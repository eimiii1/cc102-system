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
    // Mallari (movieId 0)
    {0, "10:00 AM", "Cinema 1", 180.00},
    {0, "1:00 PM",  "Cinema 1", 180.00},
    {0, "7:00 PM",  "Cinema 1", 220.00},
    // Rewind (movieId 1)
    {1, "11:00 AM", "Cinema 2", 160.00},
    {1, "3:00 PM",  "Cinema 2", 160.00},
    {1, "8:00 PM",  "Cinema 2", 200.00},
    // Dead Balag (movieId 2)
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
int getInt(string prompt);
double getDouble(string prompt);
string getString(string prompt);
void saveData();
void loadData();

int main() {
    // Initialize all seats to available
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

int getInt(string prompt) {
    int val;
    cout << prompt;
    while (!(cin >> val)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Press Enter to try again...";
        cin.get();
        cout << prompt;
    }
    return val;
}

double getDouble(string prompt) {
    double val;
    cout << prompt;
    while (!(cin >> val)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Press Enter to try again...";
        cin.get();
        cout << prompt;
    }
    return val;
}

string getString(string prompt) {
    string val;
    cout << prompt;
    while (true) {
        getline(cin, val);
        if (!val.empty()) break;
        cout << "Input cannot be empty. Press Enter to try again...";
        cin.get();
        cout << prompt;
    }
    return val;
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
    choice = getInt("\nSelect choice: ");
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
                // Count available seats
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

    int movieChoice;
    while (true) {
        movieChoice = getInt("\nSelect movie (1-" + to_string(MAX_MOVIES) + "): ") - 1;
        if (movieChoice >= 0 && movieChoice < MAX_MOVIES) break;
        cout << "Invalid movie. Press Enter to try again...";
        cin.ignore(1000, '\n');
        cin.get();
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

    int stChoice;
    while (true) {
        stChoice = getInt("\nSelect showtime (1-" + to_string(count) + "): ") - 1;
        if (stChoice >= 0 && stChoice < count) break;
        cout << "Invalid showtime. Press Enter to try again...";
        cin.ignore(1000, '\n');
        cin.get();
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

    int seatChoice;
    while (true) {
        seatChoice = getInt("\nSelect seat (1-" + to_string(MAX_SEATS) + "): ") - 1;
        if (seatChoice < 0 || seatChoice >= MAX_SEATS) {
            cout << "Invalid seat. Press Enter to try again...";
            cin.ignore(1000, '\n');
            cin.get();
        } else if (showtimes[stIndex].seats[seatChoice]) {
            cout << "Seat already taken. Press Enter to try again...";
            cin.ignore(1000, '\n');
            cin.get();
        } else {
            break;
        }
    }

    cin.ignore();
    string buyerName = getString("\nEnter your name: ");

    cout << "\n--- Booking Summary ---\n";
    cout << "Movie   : " << movies[movieChoice].title << "\n";
    cout << "Time    : " << showtimes[stIndex].time << "\n";
    cout << "Cinema  : " << showtimes[stIndex].cinema << "\n";
    cout << "Seat    : " << seatChoice + 1 << "\n";
    cout << "Price   : PHP " << showtimes[stIndex].price << "\n";
    cout << "Name    : " << buyerName << "\n";
    cout << "-----------------------\n";

    int confirm;
    while (true) {
        confirm = getInt("Confirm? (1 = Yes, 0 = No): ");
        if (confirm == 0 || confirm == 1) break;
        cout << "Please enter 1 or 0. Press Enter to try again...";
        cin.ignore(1000, '\n');
        cin.get();
    }

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

    int method;
    while (true) {
        method = getInt("Select payment method: ");
        if (method >= 1 && method <= 3) break;
        cout << "Invalid method. Press Enter to try again...";
        cin.ignore(1000, '\n');
        cin.get();
    }

    if (method == 1) {
        cout << "Amount due: PHP " << price << "\n";
        double cash;
        while (true) {
            cash = getDouble("Enter cash amount: PHP ");
            if (cash >= price) break;
            cout << "Insufficient amount. Press Enter to try again...";
            cin.ignore(1000, '\n');
            cin.get();
        }
        cout << "Change: PHP " << cash - price << "\n";
        cout << "Payment successful!\n";
        return true;
    } else {
        string methodName = (method == 2) ? "GCash" : "Maya";
        cin.ignore();
        string number = getString("Enter " + methodName + " number: ");
        string refNumber = getString("Enter reference number: ");
        cout << "Payment confirmed! Ref#: " << refNumber << "\n";
        return true;
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
            for (int i = 0; i <= (int)line.size(); i++) {
                if (i == (int)line.size() || line[i] == '|') {
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