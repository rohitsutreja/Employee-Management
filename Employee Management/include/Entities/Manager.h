#pragma once
#include "Employee.h"

namespace Entity {

	class Manager : public Employee {
	public:
		Manager() = default;

		bool getUserInput() noexcept;
		bool getUserInputForUpdate() noexcept;	
		void display() const;

		static std::optional<Manager> getManagerById(int id);
		static std::vector<Manager> getMultipleManagers(const std::string& queryField = "", const std::string& queryValue = "");
		bool save() const;
		bool update() const;
		bool deleteThis() const;

		const char* getClassName() const override;

		int getManagementExperience() const { return management_experience; }
		const std::string& getProjectTitle() const { return project_title; }

		bool setManagementExperience(int management_experience) {
			if (management_experience >= 0 && management_experience < 100) {
				this->management_experience = management_experience;
				return true;
			}
			return false;

		}
		bool setProjectTitle(std::string_view project_title) {
			this->project_title = project_title;
			return true;
		}


	private:
		int management_experience{};
		std::string project_title;
	};

}