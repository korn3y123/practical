cmake_minimum_required(VERSION 4.3)
project(practical)

set(CMAKE_CXX_STANDARD 20)

add_executable(practical src/main.cpp
        src/Client.cpp
        include/Client.h
        src/LoanApplication.cpp
        include/LoanApplication.h
        src/Loan.cpp
        include/Loan.h
        src/ConsumerLoan.cpp
        include/ConsumerLoan.h
        src/Scoring.cpp
        include/Scoring.h
        src/Contract.cpp
        include/Contract.h
        src/PaymentSchedule.cpp
        include/PaymentSchedule.h
        src/Bank.cpp
        include/Bank.h
        src/Menu.cpp
        include/Menu.h
        src/ApplicationStatus.cpp
        include/ApplicationStatus.h)
