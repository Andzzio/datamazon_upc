#pragma once
#include <iostream>
#include <string>

using namespace std;

class Shipment {
private:
    string trackingCode;
    string destination;
    string courier;

public:
    Shipment(string trackingCode, string destination, string courier) {
        this->trackingCode = trackingCode;
        this->destination = destination;
        this->courier = courier;
    }

    string getTrackingCode() { return trackingCode; }
    string getDestination() { return destination; }
    string getCourier() { return courier; }

    void show() {
        cout << "================================" << endl;
        cout << "  GUIA DE ENVIO" << endl;
        cout << "  Tracking: " << trackingCode << endl;
        cout << "  Destino : " << destination << endl;
        cout << "  Courier : " << courier << endl;
        cout << "================================" << endl;
    }

    ~Shipment() {}
};
