import java.io.*;
import java.time.*;
import java.util.*;

enum Size {
    SMALL, MEDIUM, LARGE
}

interface ParkingRatePolicy {
    int calculateFee(Duration parkedDuration, Size vehicleSize);
}

abstract class Vehicle {
    private String licensePlate;
    private LocalDateTime entryTime;

    public Vehicle(String licensePlate) {
        this.licensePlate = licensePlate;
        this.entryTime = LocalDateTime.now();
    }

    public abstract Size getSize();

    public String getLicensePlate() {
        return licensePlate;
    }

    public LocalDateTime getEntryTime() {
        return entryTime;
    }

    public void setEntryTime(LocalDateTime entryTime) {
        this.entryTime = entryTime;
    }
}

class Car extends Vehicle {
    public Car(String licensePlate) {
        super(licensePlate);
    }

    @Override
    public Size getSize() {
        return Size.MEDIUM;
    }
}

class Motorcycle extends Vehicle {
    public Motorcycle(String licensePlate) {
        super(licensePlate);
    }

    @Override
    public Size getSize() {
        return Size.SMALL;
    }
}

class Bus extends Vehicle {
    public Bus(String licensePlate) {
        super(licensePlate);
    }

    @Override
    public Size getSize() {
        return Size.LARGE;
    }
}

class ParkingSpot {
    private String spotId;
    private Size size;
    private boolean isOccupied;
    private Vehicle parkedVehicle;

    public ParkingSpot(String spotId, Size size) {
        this.spotId = spotId;
        this.size = size;
        this.isOccupied = false;
    }

    public String getSpotId() {
        return spotId;
    }

    public boolean fitVehicle(Vehicle v) {
        if (isOccupied) return false;
        Size vehicleSize = v.getSize();
        return switch (size) {
            case LARGE -> true;
            case MEDIUM -> vehicleSize != Size.LARGE;
            case SMALL -> vehicleSize == Size.SMALL;
        };
    }

    public boolean park(Vehicle v) {
        if (!fitVehicle(v)) return false;
        this.parkedVehicle = v;
        this.isOccupied = true;
        return true;
    }

    public void leave() {
        this.parkedVehicle = null;
        this.isOccupied = false;
    }
}

class Level {
    private List<ParkingSpot> spots;
    private String levelId;

    public Level(String levelId, List<ParkingSpot> spots) {
        this.levelId = levelId;
        this.spots = spots;
    }

    public ParkingSpot findAvailableSpot(Vehicle v) throws NoAvailableSpotException {
        for (ParkingSpot spot : spots) {
            if (spot.fitVehicle(v)) return spot;
        }
        throw new NoAvailableSpotException("No available spot for vehicle: " + v.getLicensePlate());
    }

    public String getLevelId() {
        return levelId;
    }

    public List<ParkingSpot> getSpots() {
        return spots;
    }
}

class Ticket {
    private String ticketId;
    private Vehicle vehicle;
    private String spotId;
    private String levelId;
    private LocalDateTime entryTime;

    public Ticket(String ticketId, Vehicle vehicle, String levelId, String spotId) {
        this.ticketId = ticketId;
        this.vehicle = vehicle;
        this.levelId = levelId;
        this.spotId = spotId;
        this.entryTime = vehicle.getEntryTime();
    }

    public String getTicketId() {
        return ticketId;
    }

    public Vehicle getVehicle() {
        return vehicle;
    }

    public LocalDateTime getEntryTime() {
        return entryTime;
    }

    public String getLevelId() {
        return levelId;
    }

    public String getSpotId() {
        return spotId;
    }
}

class Receipt {
    private String ticketId;
    private LocalDateTime exitTime;
    private int totalFee;

    public Receipt(String ticketId, LocalDateTime exitTime, int totalFee) {
        this.ticketId = ticketId;
        this.exitTime = exitTime;
        this.totalFee = totalFee;
    }

    @Override
    public String toString() {
        return "\n--- Receipt ---\n" +
               "Ticket ID: " + ticketId + "\n" +
               "Exit Time: " + exitTime + "\n" +
               "Total Fee: $" + totalFee + "\n----------------";
    }
}

class NoAvailableSpotException extends Exception {
    public NoAvailableSpotException(String message) {
        super(message);
    }
}

class InvalidTicketException extends Exception {
    public InvalidTicketException(String message) {
        super(message);
    }
}

class HourlyRatePolicy implements ParkingRatePolicy {
    public int calculateFee(Duration duration, Size size) {
        long hours = duration.toMinutes() / 60;
        if (duration.toMinutes() % 60 != 0) hours++;
        return (int) (hours * switch (size) {
            case SMALL -> 5;
            case MEDIUM -> 10;
            case LARGE -> 15;
        });
    }
}

class DailyRatePolicy implements ParkingRatePolicy {
    public int calculateFee(Duration duration, Size size) {
        long days = duration.toHours() / 24;
        if (duration.toHours() % 24 != 0) days++;
        return (int) (days * 20);
    }
}

class ParkingLot {
    private List<Level> levels;
    private Map<String, Ticket> activeTickets;
    private ParkingRatePolicy ratePolicy;

    public ParkingLot(List<Level> levels, ParkingRatePolicy ratePolicy) {
        this.levels = levels;
        this.ratePolicy = ratePolicy;
        this.activeTickets = new HashMap<>();
    }

    public String parkVehicle(Vehicle v) throws NoAvailableSpotException {
        for (Level level : levels) {
            try {
                ParkingSpot spot = level.findAvailableSpot(v);
                if (spot.park(v)) {
                    String ticketId = UUID.randomUUID().toString();
                    Ticket ticket = new Ticket(ticketId, v, level.getLevelId(), spot.getSpotId());
                    activeTickets.put(ticketId, ticket);
                    return ticketId;
                }
            } catch (NoAvailableSpotException ignored) {}
        }
        throw new NoAvailableSpotException("No available spots in entire lot.");
    }

    public Receipt unparkVehicle(String ticketId) throws InvalidTicketException {
        Ticket ticket = activeTickets.get(ticketId);
        if (ticket == null) throw new InvalidTicketException("Invalid Ticket ID: " + ticketId);

        for (Level level : levels) {
            if (level.getLevelId().equals(ticket.getLevelId())) {
                for (ParkingSpot spot : level.getSpots()) {
                    if (spot.getSpotId().equals(ticket.getSpotId())) {
                        spot.leave();
                        break;
                    }
                }
                break;
            }
        }

        LocalDateTime now = LocalDateTime.now();
        Duration duration = Duration.between(ticket.getEntryTime(), now);
        int fee = ratePolicy.calculateFee(duration, ticket.getVehicle().getSize());
        activeTickets.remove(ticketId);
        return new Receipt(ticketId, now, fee);
    }
}

public class Main {
    public static void main(String[] args) {
        try {
            List<ParkingSpot> level1Spots = Arrays.asList(
                new ParkingSpot("L1S1", Size.SMALL),
                new ParkingSpot("L1M1", Size.MEDIUM),
                new ParkingSpot("L1L1", Size.LARGE)
            );

            List<ParkingSpot> level2Spots = Arrays.asList(
                new ParkingSpot("L2M1", Size.MEDIUM),
                new ParkingSpot("L2L1", Size.LARGE)
            );

            Level level1 = new Level("Level1", new ArrayList<>(level1Spots));
            Level level2 = new Level("Level2", new ArrayList<>(level2Spots));

            ParkingLot lot = new ParkingLot(Arrays.asList(level1, level2), new HourlyRatePolicy());

            Vehicle car = new Car("CAR123");
            car.setEntryTime(LocalDateTime.now().minusHours(3).minusMinutes(30));

            Vehicle bus1 = new Bus("BUS999");
            Vehicle bus2 = new Bus("BUS888");

            String ticketCar = lot.parkVehicle(car);
            String ticketBus = lot.parkVehicle(bus1);
            
            try {
                lot.parkVehicle(bus2);
            } catch (NoAvailableSpotException e) {
                System.out.println("Expected Exception: " + e.getMessage());
            }

            Thread.sleep(1000);

            Receipt receipt = lot.unparkVehicle(ticketCar);
            System.out.println(receipt);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}