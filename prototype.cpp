#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

const int MAX_MOVIES = 10;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printDivider(char c = '=', int len = 58) {
    cout << "  ";
    for (int i = 0; i < len; i++) cout << c;
    cout << "\n";
}

void printHeader(const char* title) {
    clearScreen();
    printDivider();
    cout << "  ROBINSON'S MALL CINEMAS\n";
    printDivider('-');
    cout << "  " << title << "\n";
    printDivider();
    cout << "\n";
}

void safeCopy(char* dest, const char* src, int maxLen) {
    strncpy(dest, src, maxLen - 1);
    dest[maxLen - 1] = '\0';
}

class Movie {
private:
    int id;
    char title[80];
    char rating[5];
    int durationMins;
    char genre[30];
    bool nowShowing;

public:
    Movie() : id(0), durationMins(0), nowShowing(false) {
        title[0] = rating[0] = genre[0] = '\0';
    }

    void set(int _id, const char* _title, const char* _rating,
             int _dur, const char* _genre) {
        id = _id;
        durationMins = _dur;
        nowShowing = true;
        safeCopy(title, _title, 80);
        safeCopy(rating, _rating, 5);
        safeCopy(genre, _genre, 30);
    }

    bool isShowing() const { return nowShowing; }

    void display() const {
        cout << "  [" << id << "] " << title << "\n";
        cout << "      Rating: " << rating
             << " | Genre: " << genre
             << " | Duration: " << durationMins << " mins\n";
    }
};

class CinemaSystem {
private:
    Movie movies[MAX_MOVIES];
    int movieCount;

    void loadData() {
        movies[0].set(1, "Hello, Love, Again", "G", 115, "Romance/Drama");
        movies[1].set(2, "Aswang Chronicles", "R16", 105, "Horror");
        movies[2].set(3, "Darna: Rising", "PG", 130, "Action/Fantasy");
        movies[3].set(4, "Barracuda Boys", "R13", 95, "Comedy/Drama");
        movies[4].set(5, "The Last Sundalo", "R16", 140, "War/Drama");
        movieCount = 5;
    }

    void displayNowShowing() {
        printHeader("NOW SHOWING");

        for (int i = 0; i < movieCount; i++) {
            if (movies[i].isShowing()) {
                movies[i].display();
                cout << "\n";
            }
        }
    }

public:
    CinemaSystem() {
        movieCount = 0;
        loadData();
    }

    void run() {
        int choice;

        do {
            printHeader("MAIN MENU");

            cout << "  [1] Now Showing\n";
            cout << "  [0] Exit (Prototype)\n\n";
            cout << "  Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    displayNowShowing();
                    cout << "\n  Press ENTER to continue...";
                    cin.ignore();
                    cin.get();
                    break;

                case 0:
                    break;

                default:
                    cout << "  Invalid choice.\n";
                    cin.ignore();
                    cin.get();
            }

        } while (choice != 0);

        printHeader("END");
        cout << "  Prototype ended.\n";
    }
};

int main() {
    CinemaSystem system;
    system.run();
    return 0;
}