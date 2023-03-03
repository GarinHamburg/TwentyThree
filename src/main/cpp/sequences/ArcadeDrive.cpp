#include "sequences/ArcadeDrive.h"

ArcadeDrive::ArcadeDrive(DriveSubsystem* subsystem)
	: m_drive(subsystem) {
	AddRequirements({ subsystem });
}

void ArcadeDrive::Initialize() { }

void ArcadeDrive::Execute() {
	m_drive->ArcadeDrive(-m_driverController.GetLeftY(), m_driverController.GetRightX());

	frc::SmartDashboard::PutNumber("Forward speed:", -m_driverController.GetLeftY());
	frc::SmartDashboard::PutNumber("Turning speed:", -m_driverController.GetRightX());
	if (m_driverController.GetLeftTriggerAxis() < m_driverController.GetRightTriggerAxis()) {
		m_drive->MoveArm(m_driverController.GetRightTriggerAxis());
		frc::SmartDashboard::PutString("Arm status:", "MOVING UP");
	} else {
		if (m_driverController.GetLeftTriggerAxis() > m_driverController.GetRightTriggerAxis()) {
			m_drive->MoveArm((-m_driverController.GetLeftTriggerAxis()) * 0.5);
			frc::SmartDashboard::PutString("Arm status:", "MOVING DOWN");
		};
	}
	if (m_driverController.GetLeftTriggerAxis() == m_driverController.GetRightTriggerAxis()) {
		m_drive->MoveArm(0.0);
		frc::SmartDashboard::PutString("Arm status:", "NOT MOVING");
	}

	if (m_driverController.GetAButton() == 1 && m_driverController.GetBButton() == 0) {
		m_drive->ArmGrab();
	}
	if (m_driverController.GetBButton() == 1 && m_driverController.GetAButton() == 0) {
		m_drive->ArmRelease();
	}
	if (m_driverController.GetBButton() == 0 && m_driverController.GetAButton() == 0) {
		m_drive->ArmRest();
	}
}

void ArcadeDrive::End(bool interrupted) { }

bool ArcadeDrive::IsFinished() { return false; }