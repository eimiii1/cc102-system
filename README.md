# CC102

# Overview

This is a C++ console-based cinema system that lets users view movies, check showtimes, and book tickets. The system runs in a loop using a menu.

## System Initialization

When the program starts, the system:

- Creates the CinemaSystem object
- Loads predefined data (movies, cinemas, showtimes)
- Sets initial counters (tickets = 0, etc.)

After loading, the system goes to the main menu.

## Main Menu Flow

The system shows a menu repeatedly. The user can choose:

1. Now Showing
2. View All Showtimes
3. Book Ticket
4. View Cinemas
5. View Sold Tickets
6. Exit

After each action, the system returns to the menu.

### Now Showing (Option 1)

- Displays all movies marked as “now showing”
- Shows title, rating, genre, and duration
- No input required from user
- Returns to menu after display

### View Showtimes (Option 2)

- Displays all movies
- Shows available showtimes per movie
- Includes time, cinema, seats, and price
- Returns to menu

### Book Ticket (Option 3)

This is the main feature:

- User selects a movie ID
- System shows showtimes for that movie
- User selects a showtime ID
- System checks seat availability
- User selects a seat
- User enters name
- System shows booking summary
- User confirms booking
- System processes payment
- Seat is marked as taken
- Ticket is created and saved
- Ticket receipt is displayed

#### Payment Flow

- User selects payment method
- Cash requires input amount and checks change
- Digital payments are auto-confirmed
- If successful → booking continues
- If failed → booking stops

#### Seat System

- Shows seat map
- Checks if seat is valid and available
- Marks seat as taken after booking

#### Ticket System

Each ticket stores:

- Receipt number
- Movie name
- Cinema
- Date & time
- Seat number
- Price
- Buyer name

Ticket is displayed after booking.

### Cinemas (Option 4)

- Shows list of cinemas
- Includes type and seat capacity

### Sold Tickets (Option 5)

- Displays all booked tickets
- If none, shows empty message

### System Loop

- System keeps running after each action
- Only stops when user selects exit (0)

## Summary

This system simulates a real cinema booking process with:

- Movie browsing
- Showtime selection
- Seat reservation
- Payment simulation
- Ticket generation