#pragma once
#include "../../Domain/Entities/Order.h"
#include "../../Domain/Entities/Invoice.h"
#include "../../Domain/Entities/Shipment.h"
#include "../../Domain/Structures/Queue.h"
#include "../../Domain/Structures/Graph.h"
#include <ctime>

class ProcessOrderUseCase {
private:
    Queue<Order*>* orderQueue;
    Graph<string>* deliveryGraph;
    int invoiceCounter;
    int shipmentCounter;

public:
    ProcessOrderUseCase() {
        orderQueue = new Queue<Order*>();
        invoiceCounter = 1001;
        shipmentCounter = 5001;

        deliveryGraph = new Graph<string>(8);
        deliveryGraph->setVertex(0, "Lima Centro", 200, 280);
        deliveryGraph->setVertex(1, "Lima Norte", 150, 250);
        deliveryGraph->setVertex(2, "Arequipa", 350, 360);
        deliveryGraph->setVertex(3, "Trujillo", 90, 190);
        deliveryGraph->setVertex(4, "Cusco", 400, 280);
        deliveryGraph->setVertex(5, "Chiclayo", 70, 120);
        deliveryGraph->setVertex(6, "Piura", 50, 50);
        deliveryGraph->setVertex(7, "Ica", 240, 330);

        deliveryGraph->addEdge(6, 5, 250);
        deliveryGraph->addEdge(5, 3, 200);
        deliveryGraph->addEdge(3, 1, 500);
        deliveryGraph->addEdge(1, 0, 15);
        deliveryGraph->addEdge(0, 7, 300);
        deliveryGraph->addEdge(7, 2, 500);
        deliveryGraph->addEdge(2, 4, 300);
        deliveryGraph->addEdge(0, 4, 1100);
    }

    ~ProcessOrderUseCase() {
        delete orderQueue;
        delete deliveryGraph;
    }

    void addOrder(Order* order) {
        orderQueue->enqueue(order);
    }

    Queue<Order*>* getOrderQueue() {
        return orderQueue;
    }

    Graph<string>* getDeliveryGraph() {
        return deliveryGraph;
    }

    Order* processNextOrder() {
        if (orderQueue->isEmpty()) return nullptr;
        Order* order = orderQueue->peek();
        order->setStatus("completado");
        orderQueue->dequeue();
        return order;
    }

    int calculateDeliveryRoute(int startNode, int endNode, int* path, int& pathLength) {
        return deliveryGraph->dijkstra(startNode, endNode, path, pathLength);
    }

    Invoice* generateInvoice(Order* order) {
        time_t now = time(0);
        char dateStr[26];
        ctime_s(dateStr, sizeof(dateStr), &now);
        string date(dateStr);
        if (!date.empty() && date.back() == '\n') date.pop_back();

        double tax = order->getTotal() * 0.18;
        double totalNet = order->getTotal() + tax;
        return new Invoice(invoiceCounter++, order->getId(), date, tax, totalNet);
    }

    Shipment* generateShipment(Order* order, string destination) {
        string tracking = "TRK" + to_string(100000 + (rand() % 900000));
        string courier = (rand() % 2 == 0) ? "DHL Express" : "Datamazon Logistics";
        return new Shipment(tracking, destination, courier);
    }
};
