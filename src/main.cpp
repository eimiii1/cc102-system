#include <iostream>
#include <string>
#include <fstream>

#define MAX_MOVIES 3
#define MAX_SHOWTIMES 3
#define MAX_SEATS 5
#define MAX_TICKETS 50

using namespace std;

struct Movie {
    string title;
    string duration;
    string rating;
    string genre;
};

struct Showtime {
    int movieId;
    string time;
    string cinema;
    double price;
    bool seats[MAX_SEATS]; 
};

struct Cinema {
    string name;
    string type;
    int capacity;
};

struct Ticket {
    int receiptNumber;
    string movieTitle;
    string cinema;
    string datetime;
    int seatNumber;
    double price;
    string buyerName;
};

Movie movies[MAX_MOVIES] = {
    {"Mallari",    "2h 15m", "R-13", "Horror"},
    {"Rewind",     "1h 50m", "PG",   "Romance"},
    {"Dead Balag", "1h 37m", "R-16", "Thriller"},
};

Showtime showtimes[MAX_MOVIES * MAX_SHOWTIMES] = {
    // Mallari 
    {0, "10:00 AM", "Cinema 1", 180.00},
    {0, "1:00 PM",  "Cinema 1", 180.00},
    {0, "7:00 PM",  "Cinema 1", 220.00},
    // Rewind 
    {1, "11:00 AM", "Cinema 2", 160.00},
    {1, "3:00 PM",  "Cinema 2", 160.00},
    {1, "8:00 PM",  "Cinema 2", 200.00},
    // Dead Balag 
    {2, "12:00 PM", "Cinema 3", 150.00},
    {2, "4:00 PM",  "Cinema 3", 150.00},
    {2, "9:00 PM",  "Cinema 3", 190.00},
};

Cinema cinemas[3] = {
    {"Cinema 1", "Standard", MAX_SEATS},
    {"Cinema 2", "Deluxe",   MAX_SEATS},
    {"Cinema 3", "Standard", MAX_SEATS},
};

Ticket soldTickets[MAX_TICKETS];
int ticketCount = 0;

void clearScreen();
void pause();
void menu();
void selectChoice(int& choice);
void handleChoice(int& choice);
void displayMovies();
void viewShowtimes();
void bookTicket();
void viewCinemas();
void viewSoldTickets();
bool processPayment(double price);
void printTicket(Ticket t);
void saveData();
void loadData();

int main() {
    for (int i = 0; i < MAX_MOVIES * MAX_SHOWTIMES; i++) {
        for (int j = 0; j < MAX_SEATS; j++) {
            showtimes[i].seats[j] = false;
        }
    }

    int choice = 0;
    while (true) {
        menu();
        selectChoice(choice);
        clearScreen();
        handleChoice(choice);
    }

    return 0;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    cout << "\nPress Enter to return to menu...";
    cin.ignore();
    cin.get();
}

void menu() {
    cout << "\033[32m===== CINEMA BOOKING SYSTEM =====\033[0m\n\n";
    cout << "[1] Now Showing\n";
    cout << "[2] View All Showtimes\n";
    cout << "[3] Book Ticket\n";
    cout << "[4] View Cinemas\n";
    cout << "[5] View Sold Tickets\n";
    cout << "[0] Exit\n";
}

void selectChoice(int& choice) {
    cout << "\nSelect choice: ";
    cin >> choice;
}

void handleChoice(int& choice) {
    switch (choice) {
        case 1: displayMovies();    break;
        case 2: viewShowtimes();    break;
        case 3: bookTicket();       break;
        case 4: viewCinemas();      break;
        case 5: viewSoldTickets();  break;
        case 0:
            cout << "Goodbye!\n";
            exit(0);
        default:
            cout << "Invalid choice.\n";
    }
}

void displayMovies() {
    cout << "\033[32m===== NOW SHOWING =====\033[0m\n\n";
    for (int i = 0; i < MAX_MOVIES; i++) {
        cout << "[" << i + 1 << "] " << movies[i].title << "\n";
        cout << "    Genre    : " << movies[i].genre << "\n";
        cout << "    Rating   : " << movies[i].rating << "\n";
        cout << "    Duration : " << movies[i].duration << "\n\n";
    }
    pause();
}

void viewShowtimes() {
    cout << "\033[32m===== ALL SHOWTIMES =====\033[0m\n\n";
    for (int i = 0; i < MAX_MOVIES; i++) {
        cout << movies[i].title << " (" << movies[i].duration << ")\n";
        for (int j = 0; j < MAX_MOVIES * MAX_SHOWTIMES; j++) {
            if (showtimes[j].movieId == i) {
                int available = 0;
                for (int s = 0; s < MAX_SEATS; s++) {
                    if (!showtimes[j].seats[s]) available++;
                }
                cout << "  - " << showtimes[j].time
                     << " | " << showtimes[j].cinema
                     << " | Seats: " << available << "/" << MAX_SEATS
                     << " | PHP " << showtimes[j].price << "\n";
            }
        }
        cout << "\n";
    }
    pause();
}

void bookTicket() {
    cout << "\033[32m===== BOOK TICKET =====\033[0m\n\n";

    for (int i = 0; i < MAX_MOVIES; i++) {
        cout << "[" << i + 1 << "] " << movies[i].title << "\n";
    }
    cout << "\nSelect movie (1-" << MAX_MOVIES << "): ";
    int movieChoice;
    cin >> movieChoice;
    movieChoice--;

    if (movieChoice < 0 || movieChoice >= MAX_MOVIES) {
        cout << "Invalid movie.\n";
        pause();
        return;
    }

    cout << "\nShowtimes for " << movies[movieChoice].title << ":\n";
    int showtimeIds[MAX_SHOWTIMES];
    int count = 0;
    for (int j = 0; j < MAX_MOVIES * MAX_SHOWTIMES; j++) {
        if (showtimes[j].movieId == movieChoice) {
            int available = 0;
            for (int s = 0; s < MAX_SEATS; s++) {
                if (!showtimes[j].seats[s]) available++;
            }
            cout << "[" << count + 1 << "] "
                 << showtimes[j].time
                 << " | " << showtimes[j].cinema
                 << " | Seats: " << available << "/" << MAX_SEATS
                 << " | PHP " << showtimes[j].price << "\n";
            showtimeIds[count] = j;
            count++;
        }
    }

    cout << "\nSelect showtime (1-" << count << "): ";
    int stChoice;
    cin >> stChoice;
    stChoice--;

    if (stChoice < 0 || stChoice >= count) {
        cout << "Invalid showtime.\n";
        pause();
        return;
    }

    int stIndex = showtimeIds[stChoice];

    cout << "\nSeat Map for " << showtimes[stIndex].cinema << ":\n";
    cout << "[ ";
    for (int s = 0; s < MAX_SEATS; s++) {
        if (showtimes[stIndex].seats[s]) {
            cout << "X ";
        } else {
            cout << s + 1 << " ";
        }
    }
    cout << "]\n";
    cout << "(X = taken)\n";

    cout << "\nSelect seat (1-" << MAX_SEATS << "): ";
    int seatChoice;
    cin >> seatChoice;
    seatChoice--;

    if (seatChoice < 0 || seatChoice >= MAX_SEATS) {
        cout << "Invalid seat.\n";
        pause();
        return;
    }

    if (showtimes[stIndex].seats[seatChoice]) {
        cout << "Seat already taken.\n";
        pause();
        return;
    }

    cout << "\nEnter your name: ";
    cin.ignore();
    string buyerName;
    getline(cin, buyerName);

    cout << "\n--- Booking Summary ---\n";
    cout << "Movie   : " << movies[movieChoice].title << "\n";
    cout << "Time    : " << showtimes[stIndex].time << "\n";
    cout << "Cinema  : " << showtimes[stIndex].cinema << "\n";
    cout << "Seat    : " << seatChoice + 1 << "\n";
    cout << "Price   : PHP " << showtimes[stIndex].price << "\n";
    cout << "Name    : " << buyerName << "\n";
    cout << "-----------------------\n";
    cout << "Confirm? (1 = Yes, 0 = No): ";
    int confirm;
    cin >> confirm;

    if (confirm != 1) {
        cout << "Booking cancelled.\n";
        pause();
        return;
    }

    bool paid = processPayment(showtimes[stIndex].price);
    if (!paid) {
        cout << "Payment failed. Booking cancelled.\n";
        pause();
        return;
    }

    showtimes[stIndex].seats[seatChoice] = true;

    Ticket t;
    t.receiptNumber = 1000 + ticketCount + 1;
    t.movieTitle    = movies[movieChoice].title;
    t.cinema        = showtimes[stIndex].cinema;
    t.datetime      = showtimes[stIndex].time;
    t.seatNumber    = seatChoice + 1;
    t.price         = showtimes[stIndex].price;
    t.buyerName     = buyerName;

    soldTickets[ticketCount] = t;
    ticketCount++;

    saveData();

    printTicket(t);
    pause();
}


bool processPayment(double price) {
    cout << "\n--- Payment ---\n";
    cout << "[1] Cash\n";
    cout << "[2] GCash\n";
    cout << "[3] Maya\n";
    cout << "Select payment method: ";
    int method;
    cin >> method;

    if (method == 1) {
        cout << "Amount due: PHP " << price << "\n";
        cout << "Enter cash amount: PHP ";
        double cash;
        cin >> cash;
        if (cash < price) {
            cout << "Insufficient amount.\n";
            return false;
        }
        cout << "Change: PHP " << cash - price << "\n";
        cout << "Payment successful!\n";
        return true;
    } else if (method == 2 || method == 3) {
        string methodName = (method == 2) ? "GCash" : "Maya";
        cout << "Enter " << methodName << " number: ";
        string number;
        cin >> number;
        cout << "Amount due: PHP " << price << "\n";
        cout << "Enter reference number: ";
        string refNumber;
        cin >> refNumber;
        cout << "Payment confirmed! Ref#: " << refNumber << "\n";
        return true;
    } else {
        cout << "Invalid payment method.\n";
        return false;
    }
}

void printTicket(Ticket t) {
    cout << "\n\033[32m===========================\033[0m\n";
    cout << "        TICKET RECEIPT\n";
    cout << "\033[32m===========================\033[0m\n";
    cout << "Receipt # : " << t.receiptNumber << "\n";
    cout << "Name      : " << t.buyerName << "\n";
    cout << "Movie     : " << t.movieTitle << "\n";
    cout << "Cinema    : " << t.cinema << "\n";
    cout << "Time      : " << t.datetime << "\n";
    cout << "Seat      : " << t.seatNumber << "\n";
    cout << "Price     : PHP " << t.price << "\n";
    cout << "\033[32m===========================\033[0m\n";
    cout << "   Enjoy the movie! :)\n";
    cout << "\033[32m===========================\033[0m\n";
}

void viewCinemas() {
    cout << "\033[32m===== CINEMAS =====\033[0m\n\n";
    for (int i = 0; i < 3; i++) {
        cout << cinemas[i].name << "\n";
        cout << "  Type     : " << cinemas[i].type << "\n";
        cout << "  Capacity : " << cinemas[i].capacity << " seats\n\n";
    }
    pause();
}

void viewSoldTickets() {
    loadData();
    cout << "\033[32m===== SOLD TICKETS =====\033[0m\n\n";
    if (ticketCount == 0) {
        cout << "No tickets sold yet.\n";
    } else {
        for (int i = 0; i < ticketCount; i++) {
            printTicket(soldTickets[i]);
            cout << "\n";
        }
    }
    pause();
}

void saveData() {
    ofstream tf("tickets.txt");
    for (int i = 0; i < ticketCount; i++) {
        Ticket t = soldTickets[i];
        tf << t.receiptNumber << "|"
           << t.movieTitle    << "|"
           << t.cinema        << "|"
           << t.datetime      << "|"
           << t.seatNumber    << "|"
           << t.price         << "|"
           << t.buyerName     << "\n";
    }
    tf.close();

    ofstream sf("seats.txt");
    for (int i = 0; i < MAX_MOVIES * MAX_SHOWTIMES; i++) {
        for (int j = 0; j < MAX_SEATS; j++) {
            sf << showtimes[i].seats[j] << " ";
        }
        sf << "\n";
    }
    sf.close();
}

void loadData() {
    ticketCount = 0;

    ifstream tf("tickets.txt");
    if (tf.is_open()) {
        string line;
        while (getline(tf, line) && ticketCount < MAX_TICKETS) {
            Ticket t;
            int start = 0, field = 0;
            for (int i = 0; i <= line.size(); i++) {
                if (i == line.size() || line[i] == '|') {
                    string part = line.substr(start, i - start);
                    if      (field == 0) t.receiptNumber = stoi(part);
                    else if (field == 1) t.movieTitle    = part;
                    else if (field == 2) t.cinema        = part;
                    else if (field == 3) t.datetime      = part;
                    else if (field == 4) t.seatNumber    = stoi(part);
                    else if (field == 5) t.price         = stod(part);
                    else if (field == 6) t.buyerName     = part;
                    start = i + 1;
                    field++;
                }
            }
            soldTickets[ticketCount] = t;
            ticketCount++;
        }
        tf.close();
    }

    ifstream sf("seats.txt");
    if (sf.is_open()) {
        for (int i = 0; i < MAX_MOVIES * MAX_SHOWTIMES; i++) {
            for (int j = 0; j < MAX_SEATS; j++) {
                int val;
                sf >> val;
                showtimes[i].seats[j] = val;
            }
        }
        sf.close();
    }
}