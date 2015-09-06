//
//  users_and_books_.h
//  esame_prelz
//
//  Created by Ilaria Cazzaniga on 03/09/15.
//  Copyright (c) 2015 Ilaria Cazzaniga. All rights reserved.
//



#ifndef books_h
#define books_h


//enum genre {classic, adventure, historic, thriller, fantasy};


/*std::ostream& operator<<(std::ostream& os, genre g)
{
    switch(g)
    {
        case classic: os << "classic";    break;
        case adventure: os << "adventure"; break;
        case historic : os << "historic";  break;
        case thriller  : os << "thriller";   break;
        case fantasy  : os << "fantasy";   break;
        default    : os.setstate(std::ios_base::failbit);
    }
    return os;
}

std::istream &operator>> (std::istream &is, genre g)
{
    bool input_done = false;
    
    while(!input_done)
    {
        std::stringbuf rsbuf;
        std::string    line;
        
        is.get(rsbuf);
        line=rsbuf.str();
        
        if (!line.empty())
        {
            is.clear(); // We may be at EOF after reading a valid record.
            
            switch (is) {
                case classic:
                    
                    break;
                    
                
            }
            input_done = true;
            
            //controllare le acquisizioni, se avvengono giuste!
        }
        
        // cosa fa qui?
        // Reading an empty string will set std::ios::failbit, which we
        // don't want to consider an error.
        if (is.rdstate() == std::ios::failbit) is.clear();
        if (! is.good()) input_done = true;
        else
        {
            is.get();   // Skip past delimiter (newline).
            is.clear(); // Be happy if it doesn't succeed.
        }
    }
    
    return is;
}
*/




//classi
//note: per ora sto mettendo tutte le funzioni come void, non so se poi diventeranno magari funzioni che restituiscono un valore o rimangono void

//dichiarazione template
template<typename CODE> class book;
template<typename CODE>
std::ostream &operator<< (std::ostream &os, const book<CODE> b);
template<typename CODE>
std::istream &operator>> (std::istream &is, book<CODE> &b);

//template libro
template<typename CODE> class book
{
    friend std::ostream &operator<<<CODE> (std::ostream &os, const book<CODE> b);
    friend std::istream &operator>><CODE> (std::istream &is, book<CODE> &b);
    
public:
    typedef CODE value_type;
    //creator
    book(CODE& book_code, std::string author, std::string title, std::string edition, double price, int quantity, int available_quantity), std::string reader_age: m_book_code(book_code), m_author(author), m_title(title), m_edition(edition), m_genre(b_genre), m_price(price), m_quantity(quantity), m_a_quantity(available_quantity), m_reader_age(reader_age) {}
    book() {}
    //denstructor
    ~book(){}
    
    CODE  book_code() const { return m_book_code; }
    CODE& book_code()       { return m_book_code; }
    void  book_code(const CODE& new_book_code) { m_book_code = new_book_code; } // book_code assignment
    
    const std::string &get_author() const { return m_author; }
    const std::string &get_title() const { return m_title; }
    const std::string &get_edition() const { return m_edition;}
    //const genre &get_genre() const { return m_genre; }
    const std::string &get_reader_age() const { return reader_age; }
    const double &get_price() const { return m_price; }
    const int &get_quantity() const { return m_quantity; }
    const int &get_a_quantity() const { return m_a_quantity; }
    bool available();
    int &one_more_a_quantity() {m_a_quantity+=m_a_quantity;}
    int &one_less_a_quantity() {m_a_quantity-=m_a_quantity;}
    //queste saranno accessibili solo dall'admin
    int &one_more_quantity() {m_quantity+=m_quantity;}
    int &one_less_quantity() {m_quantity-=m_quantity;}
    
private:
    std::string m_book_code;
    std::string m_title;
    std::string m_author;
    std::string m_edition;
    std::string m_reader_age;
    //genre m_genre;
    double m_price;
    int m_quantity;
    int m_a_quantity; //se qui lo definisco =m_quantity, la consegna viene letta solo in compilazione, giusto? cioè, la quantita iniziale disp=quantità tot dei libri... chiedere a andre
    
};

//FZ DISPONIBILITà
bool template<typename CODE> class book::available()
{
    if (get_a_quantity!==0) {
        return true;
    } else {
        return false;
    }
}

//da ripensare is e os per SQLite
template<typename CODE>
std::ostream &operator<< (std::ostream &os, const book<CODE> b)
{
    return os << b.book_code << ": " << b.get_author << " - " << b.get_title << " - " << b.get_edition << " - età consigliata " << b.get_reader_age << " anni. Disponibilità: " << get_a_quantity << "/" << get_quantity;
    //capire come è scritto reader_age
}

//da sistemare a seconda dell'input! come sarà??
template<typename CODE>
std::istream &operator>> (std::istream &is, book<CODE> &b)
{
    bool input_done = false;
    
    while(!input_done)
    {
        std::stringbuf rsbuf;
        std::string    line;
        
        is.get(rsbuf);
        line=rsbuf.str();
        
        if (!line.empty())
        {
            is.clear(); // We may be at EOF after reading a valid record.
            
            std::size_t pos_a = line.find_first_of(':');
            std::size_t pos_b = line.find_first_of('-');
            if (pos_a == std::string::npos || pos_b == std::string::npos)
                continue; // Skip malformed lines
            b.m_author = line.substr(pos_a+2, (pos_b-pos_a-3));
            
            pos_a = line.find_first_of('-');
            if (pos_a == std::string::npos)
                continue; // Skip malformed lines
            b.m_title = line.substr(pos_b+2, (pos_a-pos_b-3));
            
            pos_b = line.find_first_of(',', pos_a+1);
            if (pos_b == std::string::npos)
                continue; // Skip malformed lines
            std::istringstream genrestr(line.substr(pos_a+2, (pos_b-pos_a-3)));
            genrestr >> b.m_genre;
            //b.m_genre = line.substr(pos_a+2, (pos_b-pos_a-3));
            //controllare come viene acquisito, perchè è un tipo enum
            pos_a=line.find_last_of('a');
            b.reader_age = line.substr(pos_b+18, (pos_a-pos_b+18));
            
            std::istringstream codestr(line.substr(0,pos_a-1));
            codestr >> b.m_book_code;
            input_done = true;
        
            //controllare le acquisizioni, se avvengono giuste!
        }
        
        // cosa fa qui?
        // Reading an empty string will set std::ios::failbit, which we
        // don't want to consider an error.
        if (is.rdstate() == std::ios::failbit) is.clear();
        if (! is.good()) input_done = true;
        else
        {
            is.get();   // Skip past delimiter (newline).
            is.clear(); // Be happy if it doesn't succeed.
        }
    }
    
    return is;
}



#endif
