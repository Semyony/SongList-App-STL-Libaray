// Workshop 7 Part 2
// reflect.txt
// Semen Khlavich
// 107305203
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "SongCollection.h"

namespace sdds {


    std::string removeSpaces(std::string t) {
        std::string t1;
        int count = 0;
        while (t[count] == ' ') {
            count++;
        }
        t.erase(0, count);
        t.erase(t.find_last_not_of(" \n\r\t") + 1);

        return t;
    }
    std::string tokenize(std::string& line, size_t length) {
        std::string token = line.substr(0, length);
        line.erase(0, length);
        return token;
    }

    SongCollection::SongCollection(std::string filename) {
        std::ifstream file(filename);
        try {
            if (!file)
            {
                throw std::runtime_error("ERROR: Cannot open file [ song.txt ].\n");
            }
        }
        catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }

        size_t i = 0;
        
        while (file && !file.eof()) {
            m_collection.push_back(Song());
            std::string line;
            std::string numbers;
            std::getline(file, line);
            std::string token = tokenize(line, 25);
            m_collection[i].m_title = removeSpaces(token);
            token = tokenize(line, 25);
            m_collection[i].m_artist = removeSpaces(token);
            token = tokenize(line, 25);
            m_collection[i].m_album = removeSpaces(token);
            token = tokenize(line, 5);
            if (token == "     ") {
                m_collection[i].m_year = 0;
            }
            else {
                m_collection[i].m_year = std::stoi(removeSpaces(token));
            }
            token = tokenize(line, 5);
            m_collection[i].m_length_song = std::stoi(removeSpaces(token));
            token = tokenize(line, 5);
            m_collection[i].m_price = std::stod(removeSpaces(token));
            i++;
        }
    }
    void SongCollection::display(std::ostream & out) const {
        size_t total_time = 0;
        for_each(m_collection.begin(), m_collection.end(), [&](const Song& theSong) {
            out << theSong << '\n';
            total_time += theSong.m_length_song;
        });
        out << std::setw(89) << std::setfill('-') << '\n' << std::setfill(' ');
        size_t min = 0;
        size_t sec = 0;
        size_t hour = 0;
        hour = total_time / 3600;
        min = (total_time % 3600) / 60;
        sec = (total_time % 3600) % 60;
        out << "| " << std::setw(77) << std::right << "Total Listening Time: " << hour << ":" << min << ":" << std::setfill('0') << std::setw(2) << sec << std::setfill(' ') << " |" << std::endl;
    }
    std::ostream& operator<<(std::ostream& out, const Song& theSong) {
        out << "| " << std::setw(20) << std::left << theSong.m_title << " | ";
        out << std::setw(15) << theSong.m_artist << " | ";
        out << std::setw(20) << theSong.m_album << " | ";
        out << std::setw(6) <<std::right<< ((theSong.m_year == 0) ? "" : std::to_string(theSong.m_year)) << " | ";
        size_t min = 0;
        size_t sec = 0;
        min = theSong.m_length_song / 60;
        sec = theSong.m_length_song % 60;
        out << min << ":" << std::setfill('0') << std::setw(2) << sec << std::setfill(' ') << " | ";
        out << theSong.m_price << " |";
        return out;
    }

    void SongCollection::sort(std::string sort_name){
        if (sort_name == "title") {
            std::sort(m_collection.begin(), m_collection.end(), [](const Song& a, const Song& b) {return a.m_title < b.m_title; });
        }if (sort_name == "length") {
            std::sort(m_collection.begin(), m_collection.end(), [](const Song& a, const Song& b) {return a.m_length_song < b.m_length_song; });
        }if (sort_name == "album") {
            std::sort(m_collection.begin(), m_collection.end(), [](const Song& a, const Song& b) {return a.m_album < b.m_album; });
        }
        
    }

    void SongCollection::cleanAlbum() {
        for_each(m_collection.begin(), m_collection.end(), [&](Song& theSong) {
            if (theSong.m_album == "[None]") {
                theSong.m_album = "";
            }
       });
    }
    bool SongCollection::inCollection(std::string artist) const {
        bool found = false;
        for_each(m_collection.begin(), m_collection.end(), [&](const Song& theSong) {
            if (theSong.m_artist == artist) {
                found = true;
            }
            
        });
        return found;
    }
    std::list<Song> SongCollection::getSongsForArtist(std::string artist) const {
        std::list<Song> artist_coll;
        for_each(m_collection.begin(), m_collection.end(), [&](const Song& theSong) {
                if (theSong.m_artist == artist) {
                    artist_coll.push_back(theSong);
                }
            });
        return artist_coll;
    }
}