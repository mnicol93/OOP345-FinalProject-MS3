// Name: Marc Nicolas Oliva
// Seneca Student ID: 130943202
// Seneca email: mnicolas-oliva@myseneca.ca
// Date of completion: 2021-07-26
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include <vector>
#include "Workstation.h"
namespace sdds {
	class LineManager
	{
	public:
		LineManager() = default;
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void linkStations();
		bool run(std::ostream& os);
		void display(std::ostream& os)const;
	private:
		std::vector<Workstation*> activeLine{ nullptr };
		size_t m_cntCustomerOrder{ 0u };
		Workstation* m_firstStation{ nullptr };
	};
}
#endif
