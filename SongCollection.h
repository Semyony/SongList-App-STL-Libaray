// Workshop 7 Part 2
// reflect.txt
// Semen Khlavich
// 107305203
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef _SONGCOLLECTION_H
#define _SONGCOLLECTION_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <algorithm>

namespace sdds {

    struct Song {
        std::string m_artist;
        std::string m_title;
        std::string m_album;
        double m_price;
        size_t m_year;
        size_t m_length_song;
    };

    class SongCollection {
        std::vector<Song> m_collection;
    public:
        SongCollection(std::string filename);
        void display(std::ostream& out) const;
        void sort(std::string sort_name);
        void cleanAlbum();
        bool inCollection(std::string artist) const;
        std::list<Song> getSongsForArtist(std::string artist) const;
    };

    std::ostream& operator<<(std::ostream& out, const Song& theSong);
}


#endif // !_SONGCOLLECTION_H

