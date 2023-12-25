#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Constants
const int NUM_TRIPS = 4;
const int NUM_COACHES = 6;
const int SEATS_PER_COACH = 80;
const int TICKET_PRICE = 25;

// Data structures to store information for each trip
vector<int> passengers_count_up(NUM_TRIPS, 0);
vector<int> passengers_count_down(NUM_TRIPS, 0);
vector<int> revenue_up(NUM_TRIPS, 0);
vector<int> revenue_down(NUM_TRIPS, 0);

// Train times
const vector<string> departure_times = {"09:00", "11:00", "13:00", "15:00"};
const vector<string> arrival_times = {"10:00", "12:00", "14:00", "16:00"};

// Function to display available tickets or 'Closed'
string display_tickets_available(int trip_index, bool is_up) {
    int available_seats = is_up ? SEATS_PER_COACH * NUM_COACHES - passengers_count_up[trip_index] : SEATS_PER_COACH * NUM_COACHES - passengers_count_down[trip_index];
    if (available_seats > 0) {
        return to_string(available_seats) + " seats available";
    } else {
        return "Seats are fully reserved-------";
    }
}

// Function to purchase tickets
void purchase_tickets(int trip_index, bool is_up) {
    cout << "Enter the number of passengers for " << (is_up ? "up" : "down") << " trip " << trip_index + 1 << " (" << departure_times[trip_index] << " - " << arrival_times[trip_index] << "): ";

    // Validate input
    int num_passengers;
    cin >> num_passengers;

    while (num_passengers < 1 || num_passengers > SEATS_PER_COACH * NUM_COACHES - passengers_count_up[trip_index]) {
        cout << "Invalid number of passengers. Available Seats are: " << SEATS_PER_COACH * NUM_COACHES - passengers_count_up[trip_index] << ": ";
        cin >> num_passengers;
    }

    // Update data structures
    if (is_up) {
        passengers_count_up[trip_index] += num_passengers;
        revenue_up[trip_index] += TICKET_PRICE * num_passengers;
    } else {
        passengers_count_down[trip_index] += num_passengers;
        revenue_down[trip_index] += TICKET_PRICE * num_passengers;
    }

    // Check for free tickets for groups
    if (num_passengers >= 10) {
        int free_tickets = num_passengers / 10;
        cout << "Congratulations--------! " << free_tickets << " passengers travel for free as part of a group." << endl;
    }

    cout << "Tickets purchased successfully--------!"<<endl<<endl;
}

// Function to display end-of-day summary
void display_end_of_day() {
    int total_passengers = 0;
    int total_revenue = 0;
    int max_passengers = 0;
    int max_passengers_index;

    cout << "\n        ===== End of the Day Summary =====" << endl;

    for (int i = 0; i < NUM_TRIPS; ++i) {
        cout << "\nTrain " << i + 1 << " (Up): " << passengers_count_up[i] << " passengers - $" << revenue_up[i] << " (" << departure_times[i] << " - " << arrival_times[i] << ")" << endl;
        cout << "Train " << i + 1 << " (Down): " << passengers_count_down[i] << " passengers - $" << revenue_down[i] << " (" << arrival_times[i] << " - " << departure_times[i] << ")" << endl;

        total_passengers += passengers_count_up[i] + passengers_count_down[i];
        total_revenue += revenue_up[i] + revenue_down[i];

        if (passengers_count_up[i] + passengers_count_down[i] > max_passengers) {
            max_passengers = passengers_count_up[i] + passengers_count_down[i];
            max_passengers_index = i + 1;
        }
    }

    cout << "\nTotal passengers for the day: " << total_passengers << endl;
    cout << "Total revenue for the day: $" << total_revenue << endl;
    cout << "Train journey with the most passengers: Train " << max_passengers_index << endl;
}

int main() {
    // Task 1: Initialize screen display for the start of the day
    cout << "      ===== Start of the Day =====" << endl;
    for (int i = 0; i < NUM_TRIPS; ++i) {
        cout << "\nTrain " << i + 1 << " (Up): " << display_tickets_available(i, true) << " - $" << revenue_up[i] << " (" << departure_times[i] << " - " << arrival_times[i] << ")" << endl;
        cout << "Train " << i + 1 << " (Down): " << display_tickets_available(i, false) << " - $" << revenue_down[i] << " (" << arrival_times[i] << " - " << departure_times[i] << ")" << endl;
    }

    // Task 2: Purchasing tickets
    cout << "\n        ===== Ticket Purchase =====" << endl;
    for (int i = 0; i < NUM_TRIPS; ++i) {
        if (display_tickets_available(i, true) != "Seats are fully reserved") {
            purchase_tickets(i, true);
        } else {
            cout << "Train " << i + 1 << " (Up): Seats are fully reserved. No more tickets can be purchased." << endl;
        }

        if (display_tickets_available(i, false) != "Seats are fully reserved") {
            purchase_tickets(i, false);
        } else {
            cout << "Train " << i + 1 << " (Down): Seats are fully reserved. No more tickets can be purchased." << endl;
        }
    }

    // Task 3: End of the day summary
    display_end_of_day();

return 0;
}