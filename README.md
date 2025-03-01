# 📊 Order-Book-System-for-Financial-Trading

A high-performance C++ Order Book System that manages and matches buy and sell orders in real-time using price-time priority. This system supports order addition, modification, cancellation, and trade execution.

🛠️ Features
	•	Order Management: Add, modify, and cancel buy and sell orders.
	•	Matching Engine: Automatically matches orders based on price and time priority.
	•	Trade Execution: Executes trades when matching orders are found and outputs transaction details.
	•	Order Priority: Implements price-time priority for fair order processing.
	•	Real-time Updates: Prints real-time trades and order status after each operation.
	•	Modular Structure: Organized with Order and OrderBook classes for scalability and maintainability.
	•	Cross-Platform Compatibility: Built using CMake for easy compilation across platforms.

📂 Project Structure

OrderBookSystem/
├── include/
│   ├── Order.h          // Defines the Order class
│   └── OrderBook.h      // Defines the OrderBook class
├── src/
│   ├── Order.cpp        // Implementation of Order class
│   ├── OrderBook.cpp    // Implementation of OrderBook class
│   └── main.cpp         // Entry point to run the system
└── CMakeLists.txt       // CMake configuration file

📌 Dependencies
	•	C++17 or higher
	•	CMake ≥ 3.10

🚀 Build and Run Instructions
	1.	Clone the Repository

git clone https://github.com/yourusername/OrderBookSystem.git
cd OrderBookSystem

	2.	Build the Project

mkdir build && cd build
cmake ..
make

	3.	Run the Order Book System

./OrderBookSystem

📥 Input Format

Commands are provided in the following format:
	•	Add Order: A,order_id,side,quantity,price
	•	A: Add Order
	•	order_id: Unique order identifier
	•	side: ‘B’ for Buy, ‘S’ for Sell
	•	quantity: Number of units to buy/sell
	•	price: Price per unit
	•	Cancel Order: X,order_id,side,quantity,price
	•	X: Cancel Order

✅ Example Input:

A,1000000,S,1,1075
A,1000001,B,9,1000
X,1000001,B,9,1000

📤 Output Format
	•	Trade Execution: T,traded_quantity,execution_price
	•	Order Removal: Remove Buy Order: order_id or Remove Sell Order: order_id
	•	Order Modification: Modify Buy Order: order_id Quantity: new_quantity

✅ Example Output:

T,1,1075
Remove Buy Order: 1000001
Modify Sell Order: 1000000 Quantity: 5

📊 Order Matching Logic
	1.	Orders are stored in separate queues for buy and sell.
	2.	Buy orders are sorted by price (descending) and time priority (FIFO).
	3.	Sell orders are sorted by price (ascending) and time priority (FIFO).
	4.	Matching occurs when the highest buy price ≥ lowest sell price.
