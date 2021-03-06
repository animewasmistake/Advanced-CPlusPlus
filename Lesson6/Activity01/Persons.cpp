#include "Persons.hpp"
#include "logger/Logger.hpp"
#include "Common.hpp"
#include <iostream>

Persons::Persons()
{
	m_Persons.reserve(CountPeopleInside);
}

void Persons::add(Person&& person)
{
	std::lock_guard<std::mutex> m_lock(m_Mutex);
	m_Persons.emplace_back(std::move(person));
	LOG_DEBUG() << "Count of persons: " << m_Persons.size();
}

Person Persons::get()
{
	std::lock_guard<std::mutex> m_lock(m_Mutex);
	if (m_Persons.empty())
	{
		throw "Empty Persons storage";
	}

	Person result = std::move(m_Persons.back());
	m_Persons.pop_back();
	return result;
}

size_t Persons::size() const
{
	return m_Persons.size();
}

void Persons::removePerson()
{
	std::lock_guard<std::mutex> m_lock(m_Mutex);
	m_Persons.pop_back();
	LOG_INFO() << "A person has been removed";
}
