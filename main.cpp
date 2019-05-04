#include <iostream>
#include <string.h>

using namespace std;

class Patient{

private:
    char * name;
    char * last_name;
    short int age;
    float height;
    float weight;

/*
char *tempMonth;
tempMonth = malloc(strlen(month) + 1);
strcpy(tempMonth, month);
*/

public:
    Patient(){
    //char *nic; //strcpy wrzucic " " jako puste
    name = (char*)malloc(strlen(" ")+1);
    last_name = (char*)malloc(strlen(" ")+1);
    strcpy(name," ");
    strcpy(last_name," ");

    age = 0;
    height = 0.0;
    weight = 0.0;
    }

    Patient(
            char * name,
            char * last_name,
            short int age,
            float height = 0.0,
            float weight = 0.0
    ){
     this->name = (char*)malloc(strlen(name)+1);
     this->last_name = (char*)malloc(strlen(last_name)+1);
     strcpy(this->name,name);
     strcpy(this->last_name,last_name);

     this->age = age;
     this->height = height;
     this->weight = weight;
    }

    char * get_name(){
        return name;
    }

    char * get_last_name(){
        return last_name;
    }

    short int get_age(){
        return age;
    }

    float get_height(){
        return height;
    }

    float get_weight(){
        return weight;
    }

    short int set_age(short int new_age){
        if (new_age>0) age=new_age;
        return age;
    }

    float set_height(float new_height){
        if(new_height>0) height=new_height;
        return height;
    }

    float set_weight(float new_weight){
        if (new_weight>0) weight=new_weight;
        return weight;
    }

    Patient(const Patient & patiento){ //copy of Patient
        name = (char*)malloc(strlen(patiento.name)+1);
        last_name = (char*)malloc(strlen(patiento.last_name)+1);
        strcpy(name,patiento.name);
        strcpy(last_name,patiento.last_name);

        age = patiento.age;
        height = patiento.height;
        weight = patiento.weight;
    }

    ~Patient(){
        delete name;
        delete last_name;

        cout<<"Object of class Patient was destroyed"<<endl;
    };

    float calc_bmi(){
        if(weight==0 || height == 0){
            cerr<<"Not enough info to calculate BMI"<<endl;
            throw 455;
        }
        float bmi = weight/(height*height);

        return bmi;
    }

    void display_all(){
        cout<<name<<" "<<last_name<<" (Age: "<<age<<", Height: "<<height<<", Weight: "<<weight<<", BMI: "<<calc_bmi()<<")"<<endl;
    }

    friend ostream& operator << (ostream& stream, Patient &patiento) {
        stream << patiento.name<<" "<<patiento.last_name<<" (Age: "<<patiento.age<<", Height: "<<patiento.height<<", Weight: "<<patiento.weight<<", BMI: "<<patiento.calc_bmi()<<")";
        return stream;
    }
};

struct List {
    Patient person;
    List * next;
};

class Clinic {

private:
    char * name;
    char * address;
    List * patients = NULL;

public:
    Clinic(char * name, char * address){
        this->name = (char*)malloc(strlen(name)+1);
        this->address = (char*)malloc(strlen(address)+1);

        strcpy(this->name, name);
        strcpy(this->address, address);
    };

    Clinic(const Clinic & clinico){ //copy of Clinic
        name = (char*)malloc(strlen(clinico.name)+1);
        address = (char*)malloc(strlen(clinico.address)+1);
        strcpy(name,clinico.name);
        strcpy(address,clinico.address);
    }

    void addPatient(Patient &patient){
        if(patients==NULL){
            patients = new List();
            patients->person = patient;
            patients->next=NULL;
            return;
        }
        List * current = patients;
        while(current->next){
            current = current->next;
        }
        current->next = new List();

        current->next->person = patient;
        current->next->next = NULL;
    }

    void removePatient (char * patientName, char * patientLastName){
        List * prev = patients;
        if(prev==NULL) return;
        List * current = prev->next;
        if(current == NULL) { //only one element in list
            if(strcmp(prev->person.get_name(), patientName)==0 && strcmp(prev->person.get_last_name(),patientLastName)==0) {
                    patients = NULL;
                    return;
            }
        }
        while(current){
            if(strcmp(current->person.get_name(), patientName)==0 && strcmp(current->person.get_last_name(),patientLastName)==0) {
                    prev->next = current->next;
                    delete current;
                    return;
            }
            prev = current;
            current = current->next;

        }
    }

    void displayPatients(){
        List * current = patients;

        cout << endl << "Patients in the clinic:" << endl;

        while(current){
            cout<<current->person<<endl;
            current = current->next;
        }

        cout << endl;
    }

    void checkBMI(char * patientName, char * patientLastName){
        List * current = patients;
        while(current){
                if(strcmp(current->person.get_name(), patientName)==0 && strcmp(current->person.get_last_name(),patientLastName)==0){
                    if(current->person.get_height()==0) {
                            cout<<"\nThis person hasn't got height specified. Write it now: \n";
                            float h;
                            cin>>h;
                            current->person.set_height(h);
                    }
                    if (current->person.get_weight()==0){
                            cout<<"\nThis person hasn't got weight specified. Write it now: \n";
                            float w;
                            cin>>w;
                            current->person.set_weight(w);
                    }

                    cout << current->person.calc_bmi();
                    return;
                }

                current = current->next;
        }
        cerr<<"specified patient is not registered in the clinic"<<endl;
    }

    void choosePatients(float givenBMI){
        cout << endl << "Patients with BMI greater than " << givenBMI << ":" << endl;

        List * current = patients;
        while(current){
            if (current->person.calc_bmi()>givenBMI) cout<<current->person<<endl;
            current = current->next;
        }

        cout << endl;
    }

    ~Clinic(){
        List * current = patients;
        while(current){
            List * pre = current;
            current = current->next;
            delete pre;
        }
        delete current;
        cout<<"Object of class Clinic was destroyed"<<endl;
    }

    void removeBMIRange(float from, float to){
        List * current = patients;
        while(current){
            if(current->person.calc_bmi()>=from && current->person.calc_bmi()<=to) {
                    removePatient(current->person.get_name(), current->person.get_last_name());
                    cout<<"DO SMIETNIKA: "<<current->person<<endl;
                    };
            current=current->next;
        }
    }
};

int main() {
    Patient janusz("Janusz","Nowak",15);
    Patient zyga("Zyga","Gwiezdnopylny",69);

    Patient bartek("Bartek","Kowalski", 100, 1.54, 54.7);
    Patient agatka("Agata","Herbata",17,2.3,120);
    Patient kopia_agatki = agatka; //deep copy of agatka
    Patient grazka("Grazyna","Druzyna",50,1.63,60);
    Patient kuba("Jakub","Rozpruwacz",43,1.72,85);
    Patient jolanta("Jolanta","Kubraczek",13,1.35,40);
    Patient wiktoria("Wiktoria","Krolowa",81,1.52,43);
    Patient lukasz("Lukasz","Nierob",19,1.92,73);
    Patient nikola("Nikola","Tesla",86,1.88,64);

    //cout<<"bartkowe bmi"<<bartek.calc_bmi()<<endl;
    //cout<<"januszowe bmi"<<janusz.calc_bmi()<<endl; terminates

    //bartek.display_all();
    //cout<<bartek;

    Clinic wichrowe_wzgorze("wichrowe wzgorze", "ul. Lipowa 12");
    wichrowe_wzgorze.addPatient(bartek);
    wichrowe_wzgorze.removePatient("Bartek","Kowalski");
    //wichrowe_wzgorze.displayPatients();

    wichrowe_wzgorze.addPatient(zyga);
    wichrowe_wzgorze.addPatient(bartek);
    wichrowe_wzgorze.addPatient(grazka);
    wichrowe_wzgorze.addPatient(jolanta);
    wichrowe_wzgorze.addPatient(janusz);
    wichrowe_wzgorze.addPatient(agatka);
    wichrowe_wzgorze.addPatient(kuba);
    wichrowe_wzgorze.addPatient(wiktoria);
    wichrowe_wzgorze.addPatient(nikola);
    wichrowe_wzgorze.addPatient(lukasz);
    wichrowe_wzgorze.checkBMI("Janusz","Nowak");
    wichrowe_wzgorze.checkBMI("Zyga","Gwiezdnopylny");

    wichrowe_wzgorze.displayPatients();

    wichrowe_wzgorze.choosePatients(22);

    wichrowe_wzgorze.removeBMIRange(18.5,24.9);

    cout<<"after deleting range"<<endl;
    wichrowe_wzgorze.displayPatients();

    return 0;
}
