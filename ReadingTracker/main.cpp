#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class Book{
private:
    static int totalBooks; //nr of books
    const int id;
    char* title;
    char* author;
    int nrPages;
    char genre; // char r-romance; f-fantasy; c-comedy; s-scientific; m-murder_mystery
public:
    Book();
    Book(char* title,char* author,int nrPages,char genre);
    ~Book();
    Book(const Book &obj);
    Book& operator=(const Book &obj);

    friend ostream& operator<<(ostream&, const Book&);
    friend istream& operator>>(istream&, Book&);

    // getters
    static int getTotalBooks();
    const char* getTitle() const;
    const char* getAuthor() const;
    int getNrPages() const;
    char getGenre() const;

    // setters
    void setTitle(char*);
    void setAuthor(char*);
    void setNrPages(int);
    void setGenre(char);

    void printBook();
};
Book::Book():id(totalBooks++){
    title = strcpy( new char[4], "N/A");
    author = strcpy( new char[4], "N/A");
    nrPages = 0;
    genre = '-';
}
Book::Book(char* title,char* author,int nrPages,char genre): id(totalBooks++){  /// constructor clasa AddBook
    this->title = new char[strlen(title)+1];
    strcpy(this->title,title);

    this->author = new char[strlen(author)+1];
    strcpy(this->author,author);

    this->nrPages = nrPages;
    this->genre = genre;
}
Book::Book(const Book& obj): id(totalBooks++){  /// copy constructor clasa AddBook
    this->title = strcpy(new char[strlen(obj.title)+1], obj.title);
   // strcpy(this->title,obj.title);

    this->author =  strcpy(new char[strlen(obj.author)+1], obj.author);
   // strcpy(this->author,obj.author);

    this->nrPages = obj.nrPages;
    this->genre = obj.genre;
}
Book::~Book() {   /// deconstructor clasa AddBook
    delete[] title;
    delete[] author;
}
Book& Book::operator=(const Book &obj){  /// operator= clasa AddBook

    if(this == &obj){
        return *this;
    }

    delete[] this->title;
    this->title = strcpy( new char[strlen(obj.title)+1], obj.title);

    delete[] this->author;
    this->author = strcpy( new char[strlen(obj.author)+1], obj.author);

    this->nrPages = obj.nrPages;
    this->genre = obj.genre;

    return *this;
}
const char* Book::getTitle() const{
    return title;
}
const char* Book::getAuthor() const{
    return author;
}
int Book::getNrPages() const{
    return nrPages;
}
char Book::getGenre() const{
    return genre;
}
void Book::setTitle(char* title){
    delete[] this->title;
    this->title = strcpy(new char[strlen(title)+1], title);
}
void Book::setAuthor(char* author){
    delete[] this->author;
    this->author = strcpy(new char[strlen(author)+1], author);
}
void Book::setNrPages(int nrPages){
    this->nrPages = nrPages;
}
void Book::setGenre(char genre){


    if(genre == 'r' || genre == 'f' || genre == 'c' || genre == 's' || genre == 'm')
    this->genre = genre;
}
ostream& operator<<(ostream& out, const Book& obj){  /// operator<< AddBook
    out<<"Title: "<<obj.title<<endl;
    out<<"Author: "<<obj.author<<endl;
    out<<"Number of pages: "<<obj.nrPages<<endl;
    out<<"Genre: "<<obj.genre<<endl;
    return out;
}
istream& operator>>(istream& is,  Book& obj){ /// operator>> AddBook

    char title[50], author[50];
    int pg; char gen;

    cout<<"Name of the book: ";
    is.ignore(2000, '\n');
    is.getline(title, 50);
    obj.setTitle(title);

    cout<<"Last name of the author: ";
    is.ignore(2000, '\n');
    is.getline(author, 50);
    cout << "read author name\n";
    obj.setAuthor(author);

    cout<<"Number of pages that the book has in total: ";
    is>>pg;
    obj.setNrPages(pg);

    cout<<"What genre does the book fall into? "<<endl;
    cout<<"Type r-romance; f-fantasy; c-comedy; s-scientific; m-murder_mystery: ";
    is>>gen;
    while(gen != 'r' && gen != 'f' && gen != 'c' && gen != 's' && gen != 'm'){
        cout<<"Invalid! Please type a valid character: ";
        is>>gen;
    }
   obj.setGenre(gen);

   return is;

}

int Book::totalBooks = 1;


class ReadingProgress {
private:
    static int noProgress;
    const int id;
    int* pagesRead;
    int totalPages;
    double percentage;
    float ratio;
    bool finished;
public:
    ReadingProgress();
    ReadingProgress(int, int, double, bool);
    ReadingProgress(const ReadingProgress&);
    ~ReadingProgress();

    ReadingProgress& operator=(const ReadingProgress&);
    friend ostream& operator<<(ostream&, const ReadingProgress&);
    friend istream& operator>>(istream&, ReadingProgress&);

    //setters
    void setPagesRead(int);
    void setPagesTotal(int);
    void setProcentage(double);
    void setFinished(bool);

    //getters
    bool getFinished() const;

};
void ReadingProgress::setPagesRead(int pg){
    *pagesRead = pg;
}
void ReadingProgress::setPagesTotal(int tot){
    totalPages=tot;
}
void ReadingProgress::setProcentage(double pre){
    percentage=pre;
}
void ReadingProgress::setFinished(bool fin){
    finished=fin;
}
ReadingProgress::~ReadingProgress(){
    delete pagesRead;
}
ReadingProgress::ReadingProgress():id(noProgress++) {
    pagesRead = new int;
    *pagesRead = 0;
    totalPages = 0;
    percentage = 0;
    finished = false;
}
ReadingProgress::ReadingProgress(int pagesRead, int totalPages, double percentage, bool finished):id(noProgress++){
    
    *this->pagesRead = pagesRead;
    this->totalPages = totalPages;
    this->percentage = percentage;
    this->finished = finished;
}
ReadingProgress::ReadingProgress(const ReadingProgress& prog):id(noProgress++){
    pagesRead = prog.pagesRead;
    totalPages = prog.totalPages;
    percentage = prog.percentage;
    finished = prog.finished;
}
ReadingProgress& ReadingProgress::operator=(const ReadingProgress &obj){  /// operator= clasa ReadingProgress
    if(this == &obj){
        return *this;
    }
    this->pagesRead = obj.pagesRead;
    this->totalPages = obj.totalPages;
    this->percentage = obj.percentage;
    this->finished = obj.finished;
    return *this;
}
istream& operator>>(istream& is, ReadingProgress& obj){  /// operator<< ReadingProgress
    bool fin;
    cout<<"Have you finished your book?"<<endl<<"Press 1 if you did and 0 if it's still in progress:";
    is>>fin;
    obj.setFinished(fin);

    int pg;
    cout<<"How many pages have you read in total: ";
    is>>pg;
    obj.setPagesRead(pg);
    return is;
}
ostream& operator<<(ostream& out, const ReadingProgress& obj){  /// operator<< AddBook
    out<<"You read this many pages so far: "<<*obj.pagesRead<<endl;
    out<<"In total there are this many pages: "<<obj.totalPages<<endl;
    out<<"Percentage: "<<obj.percentage<<endl;
    out<<"finish status: "<<obj.finished<<endl;
    return out;
}
bool ReadingProgress::getFinished() const{
    return finished;
}

int ReadingProgress::noProgress=0;

class Read{
private:
    int static totalBooks;
    const int id;
    Book* books[100];    // vectori de carti=colectia de carti
    ReadingProgress progress[100];

public:
    Read();
    ~Read();

    void AddBookToCollection(Book *b);
    void print_books_to_update_progress();
    void printCollection();
    void update_progress(int index);
    void show_progress();

    void sort_by_fin();
    void sort_by_unfin();
    void sort_by_gen();

    int getTotalBooks();
};
int Read::getTotalBooks(){
    return totalBooks;
}
Read::Read():id(){
    totalBooks = 0;
}
Read::~Read(){
     for(int i=0; i<totalBooks;i++){
        delete books[i];
     }
}
void Read::update_progress(int index){
    int pages;
    cout<<"How many pages have you read in total: ";
    cin>>pages;

    int total = books[index]->getNrPages();

    progress[index].setPagesRead(pages);
    progress[index].setPagesTotal(total);

    float ratio = (float) pages/ total;
    double procent = ratio * 100;
    progress[index].setProcentage(procent);

    if(pages == total)
        progress[index].setFinished(true);
    else
        progress[index].setFinished(false);

}

void Read::AddBookToCollection(Book *b){
    books[totalBooks] = b;
    totalBooks++;
}
void Read::print_books_to_update_progress(){

    if(totalBooks==0){
        cout<<"There are no books in collection yet."<<endl<<endl;
        return ;
    }
    for(int i=0;i<totalBooks;i++){
        cout<<"Book "<<i+1<<": ";
        cout<< books[i] -> getTitle() <<" by "<< books[i] -> getAuthor() <<" pages count: ";
        cout<< books[i] -> getNrPages() <<endl;

        cout<<endl;
    }
}
void Read::printCollection(){

    if(totalBooks==0){
        cout<<"There are no books in collection yet."<<endl<<endl;
        return;
    }
    for(int i=0;i<totalBooks;i++){
        cout<<"Book "<<i+1<<": "<<endl;
        books[i] -> printBook();
        cout<<endl;
    }
}
void Read::show_progress(){

    for(int i=0;i<totalBooks;i++){
        cout<<"Book: "<<books[i]->getTitle()<<endl;
        cout<<progress[i]<<endl;
    }
}
void Read::sort_by_fin(){
    for(int i=0;i<totalBooks;i++){
        if(progress[i].getFinished() == true)
        cout<<"Book: "<<books[i]->getTitle()<<endl;
        
    }
}
void Read::sort_by_unfin(){
    for(int i=0;i<totalBooks;i++){
        if(progress[i].getFinished() == false)
        cout<<"Book: "<<books[i]->getTitle()<<endl;
        
    }
}

void Read::sort_by_gen(){
    cout<<"All my romance books: ";
    for(int i=0;i<totalBooks;i++){
        if(books[i]->getGenre() == 'r')
        cout<<books[i]->getTitle()<<", ";
    }
    cout<<endl;
    cout<<"All my fantasy books: ";
    for(int i=0;i<totalBooks;i++){
        if(books[i]->getGenre() == 'f')
        cout<<books[i]->getTitle()<<", ";
    }
    cout<<endl;
    cout<<"All my comedy books: ";
    for(int i=0;i<totalBooks;i++){
        if(books[i]->getGenre() == 'c')
        cout<<books[i]->getTitle()<<", ";
    }
    cout<<endl;
    cout<<"All my murder mystery books: ";
    for(int i=0;i<totalBooks;i++){
        if(books[i]->getGenre() == 'm')
        cout<<books[i]->getTitle()<<", ";
    }
    cout<<endl;
    cout<<"All my scientific books: ";
    for(int i=0;i<totalBooks;i++){
        if(books[i]->getGenre() == 's')
        cout<<books[i]->getTitle()<<", ";
    
    }
}

int Read::totalBooks=0;


class User{
private:
    int static noUser;
    const int id;
    string name;
    Read tracker;

public:
    User();
    User(string name);

    User& operator=(const User& obj);
    friend ostream& operator<<(ostream& out, const User& obj);
    friend istream& operator>>(istream& is, User &obj);

    void setName(string name);
    string getName() const ;

    Read& getTracker();

    
    void UpdateProgress(int index);
    void ShowProgress();

};
Read& User::getTracker(){
    return tracker;
}
User::User():id(noUser++){
    name = "Anonymuos";
}
User::User(string name):id(noUser++){
    this->name = name;
}
string User::getName() const{
    return this->name;
 }
void User::setName(string name){
    this->name=name;
 }
ostream& operator<<(ostream& out, const User& obj){
    out<<obj.name;
    return out;
 }
istream& operator>>(istream &is, User &obj){
    is>>obj.name;
    return is;
 }
User& User::operator=(const User& obj){
    if(this != &obj)
        this->name= obj.name;
    return *this;
}

int User::noUser=0;

void case1_adding_book(Read &tracker) {
    cout<<"----------------------------------------------- Reading Tracker ------------------------------------------------------ "<<endl;
    cout<<endl;
    char title[50], author[50];
    int pg;
    char gen;

    cout<<"Add new book to my collection: "<<endl;
    cout<<"Name of the book: ";
    cin.ignore();
    cin.get(title, 50);
    cin.ignore(2000, '\n');
    cout<<endl;

    cout<<"Last name of the author: ";
    cin.get(author, 50);
    cin.ignore(2000, '\n');
    cout<<endl;

    cout<<"Number of pages that the book has in total: ";
    cin>>pg;
    cout<<endl;

    cout<<"What genre does the book fall into? "<<endl;
    cout<<"Type r-romance; f-fantasy; c-comedy; s-scientific; m-murder_mystery: ";
    cin>>gen;
    while(gen != 'r' && gen != 'f' && gen != 'c' && gen != 's' && gen != 'm'){
        cout<<"Invalid! Please type a valid character: ";
        cin>>gen;
    }
    cout<<endl;

    char *ptitle=title, *pauthor=author;
    Book *book = new Book(title,author,pg,gen);
    tracker.AddBookToCollection(book);


    system("CLS");
}
void case2_see_collection(Read &tracker) {
    cout<<"----------------------------------------------- Reading Tracker ------------------------------------------------------ "<<endl;
    cout<<endl;
    cout<<"My current book collection."<<endl<<endl;

    tracker.printCollection();

    cout<<"If you want to go back to main meniu press 0"<<endl;
    int x;
    cin>>x;
    if(x==0)
        system("CLS");
}
void case3_update_progress(Read &tracker) {
    cout<<"----------------------------------------------- Reading Tracker ------------------------------------------------------ "<<endl;
    cout<<endl;
    cout<<"3. Update my reading progress."<<endl;
    tracker.print_books_to_update_progress();
    if(tracker.getTotalBooks() !=0 ){

        cout<<"Press the number of the book you would like to update: ";
        int nrBook;
        cin>>nrBook;
        if(nrBook>=1 && nrBook <= tracker.getTotalBooks())
            tracker.update_progress(nrBook-1);
        else cout <<"Invalid number!";

    }

    cout<<"If you want to go back to main meniu press 0"<<endl;
    int x;
    cin>>x;
    if(x==0)
        system("CLS");
}
void case4_show_status(Read &tracker) {
    cout<<"----------------------------------------------- Reading Tracker ------------------------------------------------------ "<<endl;
    cout<<endl;
    cout<<"4. Track my reading."<<endl;
    tracker.show_progress();

    cout<<"If you want to go back to main meniu press 0"<<endl;
    int x;
    cin>>x;
    if(x==0)
        system("CLS");
}

void case5_sort_collection(Read &tracker) {
    cout<<"----------------------------------------------- Reading Tracker ------------------------------------------------------ "<<endl;
    cout<<endl;
    cout<<"Sort by:"<<endl;
    cout<<"1. Finished books."<<endl;
    cout<<"2. In progress books."<<endl;
    cout<<"3. By genre."<<endl;
    cout<<"4. Quit."<<endl;

    cout<<"Press the number coresponding with your sorting method prefered: ";
    int button;
    cin>>button;

    switch(button) {
            case(1):{
                if(tracker.getTotalBooks() !=0 ){
                    tracker.sort_by_fin();
                }
                break; }
            case(2):{
                if(tracker.getTotalBooks() !=0 ){
                    tracker.sort_by_unfin();
                }
                break; }
            case(3):{
                if(tracker.getTotalBooks() !=0 ){
                    tracker.sort_by_gen();
                }
                   break; }
            case(4):{
                system("CLS");
                   break; }
            }
    

    cout<<"If you want to go back to main meniu press 0"<<endl;
    int x;
    cin>>x;
    if(x==0)
        system("CLS");
}

class Meniu{
private:
    vector<User> users;
    int usercurrent;
public:
    void run(); 
    void login();
};
void Meniu::login(){
    string name;
    cout<<"Enter UserName: ";
    cin>>name;
    for(int i=0;i<users.size();i++){
        if(users[i].getName() == name){
            usercurrent = i;
            cout<<"Welcome back "<<name<< " !"<<endl;
            return;
        }
    }
    User u(name);
    users.push_back(u);

    usercurrent = users.size() - 1;
    cout<<"New user created!"<<endl;
}

void Meniu::run(){

login();

 while (true) {

        Read &tracker = users[usercurrent].getTracker();


        cout<<"----------------------------------------------- Reading Tracker ------------------------------------------------------ "<<endl;
        cout<<endl; cout<<"What would you like to do?"<<endl;
        cout<<endl; cout<<"1. Add new book to my colection."<<endl;
        cout<<"2. See my current book collection."<<endl;
        cout<<"3. Update my reading progress."<<endl;
        cout<<"4. Track my reading."<<endl;
        cout<<"5. Sort my books."<<endl;
        cout<<"6. Quit."<<endl;
        cout<<endl<<"Press the number:";
        int x;
        cin>>x;
        while(x > 6) {
            cout<<"Invalid number! Please try again!"<<endl;
            cout<<"Press the number:";
            cin>>x;
            cout<<endl;
        }
        switch(x) {
            case(1):{
                system("CLS");
                case1_adding_book(tracker);
                break; }
            case(2):{
                system("CLS");
                case2_see_collection(tracker);
                break; }
            case(3):{
                system("CLS");
                case3_update_progress(tracker);
                break; }
            case(4):{
                system("CLS");
                case4_show_status(tracker);
                break; }
            case(5):{
                system("CLS");
                case5_sort_collection(tracker);
                break; }
            case(6):{
                return;
                break; }
        
        }
    }

}



void Book::printBook(){
    cout<<"Title: "<<title<<endl;
    cout<<"Author: "<<author<<endl;
    cout<<"Number of pages: "<<nrPages<<endl;
    cout<<"Genre: "<<genre<<endl;

}
int main() {
    Meniu m;
    m.run();
    return 0;
}