// Name: Marc Nicolas Oliva
// Seneca Student ID: 130943202
// Seneca email: mnicolas-oliva@myseneca.ca
// Date of completion: 2021-07-26
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <deque>
#include <string>
#include "Station.h"
#include "CustomerOrder.h"
namespace sdds {
	extern std::deque<CustomerOrder> pending;
	extern std::deque<CustomerOrder> completed;
	extern std::deque<CustomerOrder> incomplete;

	class Workstation : public Station
	{
	public:
		Workstation(const std::string& str) : Station(str) {};
		Workstation(const Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(const Workstation&) = delete;
		Workstation& operator=(Workstation&&) = delete;
		~Workstation() = default;
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* st = nullptr) { m_pNextStation = st; };
		Workstation* getNextStation()const;
		void display(std::ostream& os)const;
		Workstation& operator+=(CustomerOrder&& newOrder);
	private:
		std::deque<CustomerOrder> m_orders{};
		Workstation* m_pNextStation{ nullptr };
	};
}
#endif