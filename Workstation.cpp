// Name: Marc Nicolas Oliva
// Seneca Student ID: 130943202
// Seneca email: mnicolas-oliva@myseneca.ca
// Date of completion: 2021-07-26
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include "Workstation.h"

namespace sdds {
	Workstation::~Workstation(){
	}
	void Workstation::fill(std::ostream& os) {
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}
	}
	bool Workstation::attemptToMoveOrder() {
		if (m_orders.front().isItemFilled(this->getItemName())) {
			if (m_pNextStation == nullptr) {
				if (m_orders.front().isFilled()) {
					completed.push_back(m_orders.front());
				}
				else {
					return false;
				}
			} else {
				m_pNextStation->m_orders.push_back(m_orders.front());
			}//incomplete.push_back(m_orders.front());
			m_orders.pop_front();
			return true;
		}
		else if (!this->getQuantity()){
			if (!m_pNextStation)
				incomplete.push_back(m_orders.front());
			else
				m_pNextStation->m_orders.push_back(m_orders.front());
			m_orders.pop_front();
			return true;
		}
		return false;
	}
	Workstation* Workstation::getNextStation()const {
		return m_pNextStation;
	}
	void Workstation::display(std::ostream& os)const {
		os << this->getItemName() << "-->";
		if (m_pNextStation == nullptr)
			os << std::endl;
		else
			os << m_pNextStation->getItemName() << std::endl;
	}
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_orders.push_back(newOrder);
	}
}