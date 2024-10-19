#include <bits/stdc++.h>
using namespace std;

class Vehicle {
public:
	string regNo;
	string color;
	string type;
};

class Slot {
public:
	string typeOfVeh;
	bool occ;
	Slot()
	{
		occ = false;
	}
};

class Floor {
public:
	string no;
	vector<Slot>slots;
};

class Ticket {
public:
	string id;
};

class Parking {
public:
	Ticket t;
	Vehicle v;
};

class ParkingLot {
public:
	string id;
	vector<Floor>floors;
	vector<Parking>parkings;
	int canBeParked;
	int noOfFloors;
	int noOfSlotsPerFloor;
	map<string, pair<int, int>> mp;
	map<pair<string, int>, int> mp2;
	map<pair<string, int>, set<int>> mp3; 
    map<pair<string,int>,set<int>>mp4;
	ParkingLot(string id, int noOfFloors, int noOfSlotsPerFloor)
	{
		canBeParked = noOfFloors * noOfSlotsPerFloor;
        cout<<"Created a Parking lot with "<<noOfFloors<<" floors and "<<noOfSlotsPerFloor<<" slots per floor"<<endl;
		this->noOfSlotsPerFloor = noOfSlotsPerFloor;
		this->noOfFloors = noOfFloors;
		this->id = id;
		floors.resize(noOfFloors);

		for (int i = 0; i < noOfFloors; i++) {
			if (noOfSlotsPerFloor == 1) {
				floors[i].slots.resize(1);
				floors[i].slots[0].typeOfVeh = "Truck";
				mp2[{"Truck", i}] = 1;
				mp3[{"Truck", i}].insert(1); 
			}
			else if (noOfSlotsPerFloor == 2) {
				floors[i].slots.resize(2);
				floors[i].slots[0].typeOfVeh = "Truck";
				floors[i].slots[1].typeOfVeh = "Bike";
				mp2[{"Truck", i}] = 1;
				mp3[{"Truck", i}].insert(1); 
				mp2[{"Bike", i}] = 1;
				mp3[{"Bike", i}].insert(2); 
			}
			else if (noOfSlotsPerFloor == 3) {
				floors[i].slots.resize(3);
				floors[i].slots[0].typeOfVeh = "Truck";
				floors[i].slots[1].typeOfVeh = "Bike";
				floors[i].slots[2].typeOfVeh = "Bike";
				mp2[{"Truck", i}] = 1;
				mp3[{"Truck", i}].insert(1); 
				mp2[{"Bike", i}] = 2;
				mp3[{"Bike", i}].insert(2); 
				mp3[{"Bike", i}].insert(3); 
			}
			else {
				floors[i].slots.resize(noOfSlotsPerFloor);
				floors[i].slots[0].typeOfVeh = "Truck";
				floors[i].slots[1].typeOfVeh = "Bike";
				floors[i].slots[2].typeOfVeh = "Bike";
				mp2[{"Truck", i}] = 1;
				mp3[{"Truck", i}].insert(1); 
				mp2[{"Bike", i}] = 2;
				mp3[{"Bike", i}].insert(2); 
				mp3[{"Bike",i}].insert(3);
				for (int j = 3; j < noOfSlotsPerFloor; j++) {
					mp2[{"Car", i}]++;
					mp3[{"Car", i}].insert(j + 1); 
					floors[i].slots[j].typeOfVeh = "Car";
				}
			}
		}
	}

	void park_vehicle(string vehType, string regNo, string color)
	{
		int i, j;
		if (canBeParked == parkings.size()) {
			cout << "Parking Lot is Full\n";
			return;
		}

		for (i = 0; i < noOfFloors; i++) {
			for (j = 0; j < noOfSlotsPerFloor; j++) {
				if (floors[i].slots[j].occ == true || floors[i].slots[j].typeOfVeh != vehType) {
					continue;
				}
				else {
					string tid = id + "_" + to_string(i + 1) + "_" + to_string(j + 1);
					floors[i].slots[j].occ = true;
					Vehicle vehicle;
					vehicle.regNo = regNo;
					vehicle.color = color;
					vehicle.type = vehType;
					Ticket ticket;
					ticket.id = tid;
					Parking p;
					p.t = ticket;
					p.v = vehicle;
					parkings.push_back(p);
					mp[regNo] = {i, j};
					mp2[{vehType, i}]--;
					mp3[{vehType, i}].erase(j + 1); 
					mp4[{vehType,i}].insert(j+1);
					cout << "Vehicle parked with ticket ID: " << tid << endl;
					return;
				}
			}
		}
	}

	void unpark_vehicle(string ticket_id)
	{
		int noOfVehicles = parkings.size();
		int i;
		for (i = 0; i < noOfVehicles; i++) {
			if (parkings[i].t.id == ticket_id)
				break;
		}
		if (i >= noOfVehicles) {
			cout << "No vehicle with ticket id :-" << ticket_id << endl;
			return;
		}
		else {
			Vehicle v = parkings[i].v;
			string regNo = v.regNo;
			int fl = mp[regNo].first;
			int sl = mp[regNo].second;
			floors[fl].slots[sl].occ = false;
			mp.erase(regNo);
			mp2[{v.type, fl}]++;
			mp3[{v.type, fl}].insert(sl + 1); 
			mp4[{v.type,fl}].erase(sl+1);
			parkings.erase(parkings.begin() + i);
		}
	}

	void display_no_of_free_slots_per_floor(string type)
	{
		for (auto it : mp2) {
			string veh = it.first.first;
			int fl = it.first.second;
			if (veh == type) {
				cout << "No of free slots for the vehicle type " << veh << " at floor " << fl << " is " << it.second << endl;
			}
		}
	}

	void display_free_slots(string type)
	{
		for (auto it : mp3) {
			string veh = it.first.first;
			int fl = it.first.second;
			if (veh == type) {
			    cout << "Slots free for " << veh << " on the floor " << fl << ":-";
				for (auto jt : it.second) {
					  cout << jt <<", ";
				}
				cout<<endl;
			}
		}
	}
	void display_occ_slots(string type)
	{
	    for(int i = 0;i<noOfFloors;i++)
	    {
	        
	        if(mp4.find({type,i})!=mp4.end())
	        {
	            cout<<"Slots occupied by " << type<<"s on floor "<<i<<" are :-";
	            for(auto jt:mp4[{type,i}])
	            {
	                cout<<jt<<", ";
	            }
	            cout<<endl;
	        }
	        else{
	            cout<<"No slots occupied by "<<type<<"s on floor "<<i<<endl;
	        }
	    }
	}
};

int main()
{
    ParkingLot* p = new ParkingLot("PR1234", 2, 6);
	p->display_no_of_free_slots_per_floor("Car");
	p->display_no_of_free_slots_per_floor("Bike");
	p->display_no_of_free_slots_per_floor("Truck");
	p->display_free_slots("Car");
	p->display_free_slots("Bike");
	p->display_free_slots("Truck");
	p->display_occ_slots("Car");
	p->display_occ_slots("Bike");
	p->display_occ_slots("Truck");
	p->park_vehicle("Car","KA-01-DB-1234","black");
	p->park_vehicle("Car","KA-02-CB-1334","red");
	p->park_vehicle("Car","KA-01-DB-1133","black");
	p->park_vehicle("Car","KA-05-HJ-8432","white");
	p->park_vehicle("Car","WB-45-HO-9032","white");
	p->park_vehicle("Car","KA-01-DF-8230","black");
	p->park_vehicle("Car","KA-21-HS-2347","red");
	p->display_no_of_free_slots_per_floor("Car");
	p->display_no_of_free_slots_per_floor("Bike");
	p->display_no_of_free_slots_per_floor("Truck");
	p->unpark_vehicle("PR1234_2_5");
	p->unpark_vehicle("PR1234_2_5");
	p->unpark_vehicle("PR1234_2_7");
	p->display_no_of_free_slots_per_floor("Car");
	p->display_no_of_free_slots_per_floor("Bike");
	p->display_no_of_free_slots_per_floor("Truck");
	p->display_free_slots("Car");
	p->display_free_slots("Bike");
	p->display_free_slots("Truck");
	p->display_occ_slots("Car");
	p->display_occ_slots("Bike");
	p->display_occ_slots("Truck");
	p->park_vehicle("Bike","KA-01-DB-1541","black");
	p->park_vehicle("Truck","KA-32-SJ-5389","orange");
	p->park_vehicle("Truck","KL-54-DN-4582","green");
	p->park_vehicle("Truck","KL-12-HF-4542","green");
	p->display_no_of_free_slots_per_floor("Car");
	p->display_no_of_free_slots_per_floor("Bike");
	p->display_no_of_free_slots_per_floor("Truck");
	p->display_free_slots("Car");
	p->display_free_slots("Bike");
	p->display_free_slots("Truck");
	p->display_occ_slots("Car");
	p->display_occ_slots("Bike");
	p->display_occ_slots("Truck");
	return 0;
}
