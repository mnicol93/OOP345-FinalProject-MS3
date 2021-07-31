#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include "LineManager.h"
#include "Utilities.h"
namespace sdds {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		try {
			if (file == "") throw;
			std::fstream fileOpen(file);
			if (!fileOpen) throw;

			std::string temp, current, next;
			Utilities utils;
			size_t nPos{ 0u };
			bool more{ false };
			while (std::getline(fileOpen, temp)) {
				next = "";
				current  = utils.extractToken(temp, nPos, more);
				if (more)
					next = utils.extractToken(temp, nPos, more);

				std::for_each(stations.begin(), stations.end(), [&](Workstation* currentWs) {
					if (currentWs->getItemName() == current) {
						std::for_each(stations.begin(), stations.end(), [&](Workstation* nextWs) {
							if (nextWs->getItemName() == next)
								currentWs->setNextStation(nextWs);
						});
						activeLine.push_back(currentWs);
					}
				});
			}
			m_firstStation = activeLine.front();
			m_cntCustomerOrder = pending.size();
		}
		catch (...) {
			throw("Error reading file");
		}
	}
	void LineManager::linkStations() {
		size_t i{ 0u };
		std::vector<Workstation*> tempVec{ };
		tempVec.push_back(m_firstStation);

		std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation*) {
			std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* ws) {
				if (tempVec[i]->getNextStation()) {
					if (tempVec[i]->getNextStation()->getItemName() == ws->getItemName()) {
						tempVec.push_back(ws);
						i++;
					}
				}
			});
		});
		if(!tempVec.empty())
			activeLine = tempVec;
	}
	bool LineManager::run(std::ostream& os) {
		static size_t localCount{ 1u };
		bool complete = true;

		os << "Line Manager Iteration: " << localCount++ << std::endl;

		if (!pending.empty()) {
			/*pending[0].fillItem(*m_firstStation, os)*/
			*m_firstStation += std::move(pending.front());
			pending.pop_front();
		}
		//fill operation
		std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* st) {
			st->fill(os);
			});
		//attempt to move
		std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* st) {
			if (!st->attemptToMoveOrder()) m_cntCustomerOrder--;
			});

		return m_cntCustomerOrder<=0;
	}
	void LineManager::display(std::ostream& os) const {
		std::for_each(activeLine.begin(), activeLine.end(), [&os](const Workstation* ws) {
			ws->display(os);
			});
	}
}