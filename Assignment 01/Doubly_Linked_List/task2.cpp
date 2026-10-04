#include <iostream>
#include <string>
using namespace std;

// Doubly Linked List Node representing a Song in the Playlist
struct SongNode {
    string title;
    string artist;
    double durationMinutes;
    SongNode* prev;
    SongNode* next;

    SongNode(string t, string a, double d) {
        title = t;
        artist = a;
        durationMinutes = d;
        prev = nullptr;
        next = nullptr;
    }
};

// Music Player Playlist Manager
class MusicPlaylist {
private:
    SongNode* head;
    SongNode* tail;
    SongNode* currentSong;

public:
    MusicPlaylist() {
        head = nullptr;
        tail = nullptr;
        currentSong = nullptr;
    }

    ~MusicPlaylist() {
        SongNode* temp = head;
        while (temp != nullptr) {
            SongNode* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }

    // Add a song to the end of playlist
    void addSong(string title, string artist, double duration) {
        SongNode* newSong = new SongNode(title, artist, duration);
        if (head == nullptr) {
            head = tail = currentSong = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
        cout << "Added song: \"" << title << "\" by " << artist << endl;
    }

    // Delete a song by title
    void deleteSong(string title) {
        SongNode* curr = head;
        while (curr != nullptr && curr->title != title) {
            curr = curr->next;
        }

        if (curr == nullptr) {
            cout << "Song \"" << title << "\" not found in playlist." << endl;
            return;
        }

        if (curr == currentSong) {
            currentSong = (curr->next != nullptr) ? curr->next : curr->prev;
        }

        if (curr == head) {
            head = head->next;
            if (head) head->prev = nullptr;
            else tail = nullptr;
        } else if (curr == tail) {
            tail = tail->prev;
            if (tail) tail->next = nullptr;
            else head = nullptr;
        } else {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }

        cout << "Removed song: \"" << title << "\"" << endl;
        delete curr;
    }

    // Play next song
    void playNext() {
        if (currentSong == nullptr) {
            cout << "Playlist is empty." << endl;
        } else if (currentSong->next == nullptr) {
            cout << "Already at the last song: \"" << currentSong->title << "\"" << endl;
        } else {
            currentSong = currentSong->next;
            cout << "Now Playing: \"" << currentSong->title << "\" by " << currentSong->artist << endl;
        }
    }

    // Play previous song
    void playPrev() {
        if (currentSong == nullptr) {
            cout << "Playlist is empty." << endl;
        } else if (currentSong->prev == nullptr) {
            cout << "Already at the first song: \"" << currentSong->title << "\"" << endl;
        } else {
            currentSong = currentSong->prev;
            cout << "Now Playing: \"" << currentSong->title << "\" by " << currentSong->artist << endl;
        }
    }

    // Display playlist forwards
    void displayForward() {
        cout << "\n=== Playlist (Forward Traversal) ===" << endl;
        SongNode* temp = head;
        int index = 1;
        while (temp != nullptr) {
            cout << index++ << ". " << temp->title << " - " << temp->artist << " (" << temp->durationMinutes << " mins)";
            if (temp == currentSong) cout << "  [<-- Currently Playing]";
            cout << endl;
            temp = temp->next;
        }
    }

    // Display playlist backwards
    void displayBackward() {
        cout << "\n=== Playlist (Backward Traversal) ===" << endl;
        SongNode* temp = tail;
        int index = 1;
        while (temp != nullptr) {
            cout << index++ << ". " << temp->title << " - " << temp->artist << " (" << temp->durationMinutes << " mins)";
            if (temp == currentSong) cout << "  [<-- Currently Playing]";
            cout << endl;
            temp = temp->prev;
        }
    }
};

int main() {
    MusicPlaylist playlist;

    // Add songs
    playlist.addSong("Shape of You", "Ed Sheeran", 3.53);
    playlist.addSong("Blinding Lights", "The Weeknd", 3.20);
    playlist.addSong("Levitating", "Dua Lipa", 3.23);
    playlist.addSong("Stay", "The Kid LAROI & Justin Bieber", 2.21);

    // Display forward and backward
    playlist.displayForward();
    playlist.displayBackward();

    // Navigate playlist
    cout << "\n--- Navigation Controls ---" << endl;
    playlist.playNext();
    playlist.playNext();
    playlist.playPrev();

    // Delete a song
    cout << "\n--- Deleting Song ---" << endl;
    playlist.deleteSong("Blinding Lights");

    // Display after deletion
    playlist.displayForward();

    return 0;
}
