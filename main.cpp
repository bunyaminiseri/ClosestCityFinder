//Bunyamþin Iseri
//150130203
//Algorithms HW 3
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>  
#include <stdlib.h> 
#include <array>
#include <cmath>
#include<vector>
#include<time.h>
#define pi 3.14

using namespace std;

/*void heapSort();
void heapify(int j, int k);*/
void Swap(int i, int j);
void Shift(int heapSize, int siftNode);
void heapSort();

class City{
      public:
             City(string n, double lat, double longi){
                         name=n;
                         latitude=lat;
                         longitude=longi;
             }
        
             string getName(){
                  return name;
             }
           
             double getLat(){
                    return latitude;
             }
           
             double getLong(){
                    return longitude;
             }
             double getDistance(double lat, double longi){
                  distance = sin(latitude) * sin(lat) + cos(latitude) * cos(lat) * cos(longitude - longi);
                  distance = acos(distance);
                  distance = (6371 * pi * distance) / 180;
                  return distance;
             }
             
             
      private:
              float latitude;
              float longitude;
              string name;
              double distance;
};
vector<City> cities;
//vector<double> distances;
//vector<string> closestCities;
float mainLat;
float mainLong;

int main(int argc, char* argv[]){
  int n,k;
  clock_t t;
  n=atoi(argv[1]);
  k=atoi(argv[2]);
  mainLat=atof(argv[3]);
  mainLong=atof(argv[4]);
  
  int counter=0;
  string line;
  ifstream myfile("location.txt");
  if(myfile.is_open())
  {
	  while (getline(myfile, line))
	  {
          unsigned pos = line.find("\t"); 
		  string cityName = line.substr(0,pos);
		  line = line.substr(pos+1);
		  pos = line.find("\t");
		  float cityLatitude = atof(line.substr(0,pos).c_str());
		  line = line.substr(pos+1);
		  float cityLongitude = atof(line.substr(0,pos).c_str());
		  cities.push_back(City(cityName,cityLatitude,cityLongitude));
		  //cout<<cities[counter].getName()<<" "<<cities[counter].getLat()<<" "<<cities[counter].getLong()<<endl;
		  counter++;
		  if(counter==n) break;
	  }
	  myfile.close();
  }
  else 
	  cout << "File could not be opened." << endl;
	  t=clock();
      heapSort();
      t=clock()-t;
      cout<<endl<<"Looked up for "<<n<<" cities in "<<t<<"*10e-6 seconds."<<endl;
      ofstream outputFile;
      outputFile.open("Closest Cities.txt");
      outputFile<<"Closest cities are: "<<endl;
      for(int i=0;i<k;i++){
              outputFile<<i+1<<". "<<cities[i].getName()<<" "<<cities[i].getLat()<<" "<<cities[i].getLong()<<" "<<"Distance: "<<cities[i].getDistance(mainLat,mainLong)<<endl;
              
      
      }
      outputFile.close(); 
  return 0;
}

void Swap(int i, int j){
    if(i == j)
        return;

    City temp = cities[i];
    cities[i] = cities[j];
    cities[j] = temp;
}

void Shift(int heapSize, int shiftNode){
    int i, j;

    j = shiftNode;
    do
    {
        i = j;
        if(((2*i + 1) < heapSize) && (cities[j].getDistance(mainLat,mainLong) < cities[2*i + 1].getDistance(mainLat,mainLong)))
            j = 2*i + 1;
        if(((2*i + 2) < heapSize) && (cities[j].getDistance(mainLat, mainLong) < cities[2*i + 2].getDistance(mainLat, mainLong)))
            j = 2*i + 2;

        Swap(i, j);
    }
    while(i != j);
}

void heapSort(){
    for(int i = cities.size() - 1; i >= 0; --i){
        Shift(cities.size(), i);
        }
    for(int i = cities.size()-1; i > 0; --i){
        Swap(i, 0);
        Shift(i, 0);
    }
}
