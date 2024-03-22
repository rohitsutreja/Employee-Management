#pragma once
#include "Employee.h"

class Manager : public Employee {
public:

	Manager() = default;

	int getManagementExperience() const { return management_experience; }
	std::string getProjectTitle() const { return project_title; }


	void setManagementExperience(int management_experience) {
		this->management_experience = management_experience;
	}
	void setProjectTitle(std::string_view project_title) {
		this->project_title = project_title;
	}

	const char* getClassName() const override;

	bool getUserInputForUpdate();
	bool getUserInput();

	void display() const;
	bool save();
	bool deleteThis();
	bool update();
	static std::optional<Manager> getManagerById(int id);
	static std::vector<Manager> getMultipleManagers(const std::string& queryField = "", const std::string& queryValue = "");

private:

	int management_experience{};
	std::string project_title;
};
