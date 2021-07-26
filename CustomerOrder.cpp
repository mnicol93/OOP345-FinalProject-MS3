// Name: Marc Nicolas Oliva
// Seneca Student ID: 130943202
// Seneca email: mnicolas-oliva@myseneca.ca
// Date of completion: 2021-07-11
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <algorithm>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"
namespace sdds {
	size_t CustomerOrder::m_widthField{ 0 };

	CustomerOrder::CustomerOrder(const std::string& src) {
		Utilities util;
		size_t nPos{ 0 };
		bool more{ false };
		std::string temp{ "" };

		m_name = util.extractToken(src, nPos, more);
		m_product = util.extractToken(src, nPos, more);
		size_t listPos = nPos;
		m_cntItem = 0;

		while (more) {
			util.extractToken(src, nPos, more);
			m_cntItem++;
		}

		m_lstItem = new Item * [m_cntItem];

		for (size_t i = 0; i < m_cntItem; i++) {
			m_lstItem[i] = new Item(util.extractToken(src, listPos, more));
		}
		
		if (CustomerOrder::m_widthField < util.getFieldWidth())
			m_widthField = util.getFieldWidth();
	}
	CustomerOrder::CustomerOrder(const CustomerOrder& src) {
		throw("No copy operations allowed in CustomerOrder object.");
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
		if (this != &src) {
			m_name = src.m_name;
			src.m_name = "";

			m_product = src.m_product;
			src.m_product = "";

			m_cntItem = src.m_cntItem;
			src.m_cntItem = 0;

			m_lstItem = src.m_lstItem;
			src.m_lstItem = nullptr;
		}
		else {
			m_name = "";
			m_product = "";
			m_cntItem = 0;
			m_lstItem = nullptr;
		}
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
		if (this != &src) {

			if (m_lstItem) {
				for (size_t i = 0; i < m_cntItem; i++) {
					delete m_lstItem[i];
					m_lstItem[i] = nullptr;
				}
				delete[] m_lstItem;
				m_lstItem = nullptr;
			}

			m_name = src.m_name;
			src.m_name = "";

			m_product = src.m_product;
			src.m_product = "";

			m_cntItem = src.m_cntItem;
			src.m_cntItem = 0;

			m_lstItem = src.m_lstItem;
			src.m_lstItem = nullptr;
		}
		return *this;
	}
	CustomerOrder::~CustomerOrder() {
		if (m_lstItem) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
		}
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}
	bool CustomerOrder::isFilled() const {
		for (size_t i = 0; i < m_cntItem; i++)
			if (m_lstItem[i]->m_isFilled == false) return false;
		return true;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		for (size_t i = 0; i < m_cntItem; i++)
			if (m_lstItem[i]->m_itemName == itemName) {
				if (m_lstItem[i]->m_isFilled == false) {
					return false;
				}
			};
		return true;
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		std::for_each(m_lstItem, m_lstItem + m_cntItem, [&](Item*& item) {
			if (station.getItemName() == item->m_itemName && station.getQuantity()) {
				station.updateQuantity();
				item->m_serialnumber = station.getNextSerialNumber();
				item->m_isFilled = true;

				os << "    Filled " << m_name << ", " << m_product << " [" <<
					item->m_itemName << "]\n";
			}
		});
	}
	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;

		std::for_each(m_lstItem, m_lstItem + m_cntItem, [&](Item*& item) {
			os << "[" << std::setfill('0') << std::setw(6) << std::right << item->m_serialnumber <<
				 "] "<< std::setfill(' ') << std::setw(m_widthField) <<
				std::left << item->m_itemName << std::setfill(' ') << " - " <<
				(item->m_isFilled ? "FILLED\n" : "TO BE FILLED\n");
			});
	}
}