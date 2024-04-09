# Project Description

## Banking System Project

The Banking System project aims to develop a feature-rich and user-friendly banking solution that combines the robustness of C-based backend functionalities with the flexibility of Python-based frontend user interface.

- **Group Size:** You will work in groups of two students.
- **Data Storage:** Data will be stored in text files.
- **Sample Data:** Each group of students will create a file with at least 5 rows of sample data to be submitted with the codes and presentation slides.

### Sample Data Format
Each row in the file will have the following information, separated by commas:
- RIB
- advisorID
- username
- password
- date of birth (DD/MM/YYYY)
- net monthly salary
- total monthly loan payments
- current account balance

#### Sample data:
- 14707080701234567890139, 12345, AnnaB, tWp54@, 20/10/1995, 2500, 500.6, 7890.25
- 14707080701234567890156, 12345, Kate78, Zpt#$5, 10/05/1978, 4000, 0, 45233.99

Additionally, a file for banking advisors needs to be included. Each advisor will have an advisorID, username, password, and a list of customers identified by their RIB.

### Sample Advisor Data Format
- 12345, advisor1, pass1, 14707080701234567890139
- 12345, advisor1, pass1, 14707080701234567890156
- 20003, advisor2, pass2, 14707080701234567890300

# Project Requirements

## 1. Data Storage and Retrieval
- Load customer data from a text file into a dynamic array of structures of type Customer.
- Load advisor data from the second text file into a dynamic array of structures of type Advisor.
- Create a file “messages” to save the messages sent by customers to their advisors.

### Sample Message Data Format
Each row will have the following information, separated by commas:
- advisorID
- customerRIB
- message

#### Sample data:
- 12345, 14707080701234567890139, Hello I need an appointment to talk about a loan
- 20003, 14707080701234567890300, Please reissue my credit card ending with 0042

## 2. Core Banking Functionalities (Implemented in C)
- Implement core banking functionalities using the C programming language.
- Allow customers and banking advisors to perform essential operations such as checking account balances, transferring money, depositing, withdrawing funds, and sending/receiving messages.

## 3. Operations Supported by Your Program
- Log In
- Check Personal Details
- Update Personal Details
- Transfer Money
- Withdraw
- Deposit
- Loan Eligibility
- Send Message
- Banking advisors can perform all previous operations on customers data, except for sending messages. They can also add or delete customers.
- Log Out

## 4. Command-Line Interface (CLI) Design (Implemented in Python)
- Design a command-line interface (CLI) in Python to serve as the user interface for the banking system.
- Write a Python script that interacts with the C program.
- Design intuitive menus and prompts to guide customers and advisors through the available options and gather input from them effectively.

## 5. Testing and Debugging
- Test the integration between the Python script and the C program thoroughly.
- Debug any issues that arise during testing and refine the implementation as needed.

## 6. Documentation and Presentation
- Provide clear documentation for both the C program and the Python script.
- Prepare a short presentation to demonstrate the functionality of the banking system and discuss the implementation details.

# Important Dates
- **Deadline:** Friday, June 14th, at midnight.
- **Submission Requirements:** C and Python codes, text files containing customer information, advisor information, and messages, short documentation (6 to 8 pages), and presentation slides.
- **Presentations:** Scheduled during the lab session on the week following the deadline (Monday, June 17th, Tuesday, June 18th, and Thursday, June 20th). Each group will have 5 minutes to present their project, followed by a 5-minute question and answer period.
