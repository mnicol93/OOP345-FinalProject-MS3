#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <string>
#include "Station.h"
namespace sdds {	
	struct Item {
		std::string m_itemName;
		size_t m_serialnumber{ 0 };
		bool m_isFilled{ false };
		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder
	{
	public:
		CustomerOrder() : m_name(""), m_product(""), m_cntItem(0),
			m_lstItem(nullptr) {};
		CustomerOrder(const std::string&);
		CustomerOrder(const CustomerOrder&);
		CustomerOrder(CustomerOrder&&)noexcept;
		CustomerOrder& operator=(const CustomerOrder&) = delete;
		CustomerOrder& operator=(CustomerOrder&&)noexcept;
		virtual ~CustomerOrder();
		bool isFilled()const;
		bool isItemFilled(const std::string&)const;
		void fillItem(Station&, std::ostream&);
		void display(std::ostream&)const;
	private:
		std::string m_name;
		std::string m_product;
		size_t m_cntItem;
		Item** m_lstItem;
		static size_t m_widthField;
	};

}
#endif