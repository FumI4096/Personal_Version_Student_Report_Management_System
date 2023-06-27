#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
using namespace std;

class StudentRMSystem {
private:
    string storeSubjects[100];// will be used to store all the subjects

    string storeProcessSubjects[100];// will be used to store the subjects that will be processed
    string storePrelimsSubjects[20];// will be used to store the prelim subjects
    string storeMidtermsSubjects[20];// will be used to store the midterm subjects
    string storePrefinalsSubjects[20];// will be used to store the prefinals subjects
    string storeFinalsSubjects[20];// will be used to store the finals subjects

    double storePrelimGrades[20]; //will be used to store prelim grades
    double storeMidtermGrades[20]; //will be used to store midterm grades
    double storePrefinalGrades[20]; //will be used to store prefinal grades
    double storeFinalGrades[20]; //will be used to store final grades

    double storePrelimGradeEQ[20]; //will be used to store prelim grade equivalent
    double storeMidtermGradeEQ[20]; //will be used to store midterm grade equivalent
    double storePrefinalGradeEQ[20]; //will be used to store prefinal grade equivalent
    double storeFinalGradeEQ[20]; //will be used to store final grade equivalent

    string PrelimDescriptions[20]; //will be used to store prelim grade description
    string MidtermDescriptions[20]; //will be used to store midterm grade description
    string PrefinalDescriptions[20]; //will be used to store prefinal grade description
    string FinalDescriptions[20]; //will be used to store final grade description

    int countSub = 0; //used to count all the subjects been processed
    int prelimSubs = 0; //used to count prelim subjects been processed
    int midtermSubs = 0; //used to count midterm subjects been processed
    int prefinalSubs = 0; //used to count prefinal subjects been processed
    int finalSubs = 0; //used to count final subjects been processed

    int storeSizeSubjects = 0;// used to store how many subjects
    int Term = 0; //used to copy terms of the subject if it is prelim, midterms, prefinals, or finals

    string storePrelim; //used to store the current prelim subject
    string storeMidterm; //used to store the current midterm subject
    string storePrefinal; //used to store the current prefinal subject
    string storeFinal; //used to store the current final subject

public:
    void InpSubjects() {//a function where user inputs his/her subjects
        int sizeSub;
        cout << "Enter the number of subjects: ";
        cin >> sizeSub;//user will input how many subject does he/she want to process
        storeSizeSubjects = sizeSub;//store how many subjects here
        cin.ignore(); //clears special characters like \n,\t from cin inputs to avoid abnormal behavior of the code
        string subjects[100];
        if (sizeSub == 0){
            cout<<"No subjects to process";
            exit(0);
        }
        
        for (int i = 0; i < sizeSub; i++) {
            cout << "Enter the name for subject #" << i + 1 << ": ";
            getline(cin, subjects[i]);//User will input their subjects here

            for (int j = 0; j < i; j++) {
                if (subjects[i] == subjects[j]) {
                    cout << "You already entered this subject.";
                    i--;
                }

            }
            storeSubjects[i] = subjects[i];//subjects will be stored in this store Subjects array

        }

    }

    void RestSubjects() {//A function that asks a user if he/she is certain to its given subjects
        string pick;
        cout << endl;
        cout << "Are these your final subjects? Type 'Yes' or 'yes' to proceed,\n";
        cout << "or 'No' or 'no' to redo your subjects.\n";
        cout << "Type your response here: ";
        getline(cin, pick);
        if (pick == "Yes" || pick == "yes") {//proceeds to the next function
            cout << endl;
        }
        else if (pick == "No" || pick == "no") {//restarts to the previous function up to this function
            cout << endl;
            InpSubjects();
            RestSubjects();
        }
        else {
            cout << endl;//if user type that is not given in the program it will generate an error message 
            cout << "Invalid match. Pls Try Again!";
            RestSubjects();
        }

    }

    void DispSubjects() { //Will be used to display subjects
        cout << "======================================================\n\n";
        cout << "\tSubjects:\n\n";
        for (int i = 0; i < storeSizeSubjects; i++) {
            cout << "- " << storeSubjects[i] << endl;
        }
    }

    void InpProcessSubject() {//a function used for inputting what subject you want to process
        cout << endl;
        int term;
        bool res = true;
        string inpSub;
        bool flag = false;
        cout << endl;
        cout << "What subject would you like to process? Be careful when you type the subject,\n";
        cout << "be sure it matches one of the subjects you provided. For example,\n";
        cout << "\"Science\" and \"science\" are considered different subjects.\n";
        cout << "Type the subject here: ";
        getline(cin, inpSub);

        //a loop used to track if the subject that will be processed is equal to the previous subjects been inputted
        for (int i = 0; i < storeSizeSubjects; i++) {
            if (inpSub == storeSubjects[i]) {
                flag = true;
                break;
            }
        }

        //if user input the same subject been processed, it will generate an error message
        if (flag) {
            for (int i = 0; i < storeSizeSubjects; i++) {
                if (storeProcessSubjects[i] == inpSub) {
                    cout << endl;
                    cout << "\033[31mYou have already processed the subject: \033[0m\033[1;4m" << inpSub << "\033[0m\033[31m. Please enter a different subject.\033[0m";
                    InpProcessSubject();
                    return;
                }
            }

            //subjects will be stored sequentially
            for (int i = 0; i < storeSizeSubjects; i++) {
                if (storeProcessSubjects[i].empty()) {
                    storeProcessSubjects[i] = inpSub;
                    break;
                }
            }

            cout << endl;
            cout << "What is the subject's term? Type 1, 2, 3, or 4\n";
            cout << "[1] - Prelims\n[2] - Midterms\n[3] - Pre-finals\n[4] - Finals\n";

            //user will be asked what term is the subject, they will be stored again sequentially depending on the user's input
            while (res) {
                cout << "Type your response here: ";
                cin >> term;
                cin.ignore();
                if (term == 1) {
                    for (int i = 0; i < storeSizeSubjects; i++) {
                        if (storePrelimsSubjects[i].empty()) {
                            storePrelimsSubjects[i] = inpSub;
                            storePrelim = inpSub;
                            Term = term;
                            countSub++;
                            prelimSubs++;
                            res = false;
                            break;
                        }
                    }
                }
                else if (term == 2) {
                    for (int i = 0; i < storeSizeSubjects; i++) {
                        if (storeMidtermsSubjects[i].empty()) {
                            storeMidtermsSubjects[i] = inpSub;
                            storeMidterm = inpSub;
                            Term = term;
                            countSub++;
                            midtermSubs++;
                            res = false;
                            break;
                        }
                    }
                }
                else if (term == 3) {
                    for (int i = 0; i < storeSizeSubjects; i++) {
                        if (storePrefinalsSubjects[i].empty()) {
                            storePrefinalsSubjects[i] = inpSub;
                            storePrefinal = inpSub;
                            Term = term;
                            countSub++;
                            prefinalSubs++;
                            res = false;
                            break;
                        }
                    }
                }
                else if (term == 4) {
                    for (int i = 0; i < storeSizeSubjects; i++) {
                        if (storeFinalsSubjects[i].empty()) {
                            storeFinalsSubjects[i] = inpSub;
                            storeFinal = inpSub;
                            Term = term;
                            countSub++;
                            finalSubs++;
                            res = false;
                            break;
                        }
                    }
                }
                else {
                    cout << "\n";
                    cout << "Invalid Match. Try Again!\n";
                    res = true;
                }

            }

        }
        else {
            cout << endl;
            cout << "Your input does not match any of the subjects you provided. Please try again.";
            InpProcessSubject();
        }

        cout << endl;

    }

    void PerformScoresOP() {//a function used to compute all the scores and grades
        cout << "======================================================\n";
        cout << "Percentage Grade      Grade Point\tDescription\n\t\t       Equivalent\t\n\n";
        cout << "96.50 - 100%\t\t 1.00\t\t Excellent\n";
        cout << "92.50 - 96.49%\t\t 1.25\t\t Superior\n";
        cout << "88.50 - 92.49%\t\t 1.50\t\t Very Good\n";
        cout << "84.50 - 88.49%\t\t 1.75\t\t Good\n";
        cout << "79.50 - 84.49%\t\t 2.00\t\t Above Average\n";
        cout << "74.50 - 79.49%\t\t 2.25\t\t Average\n";
        cout << "69.50 - 74.49%\t\t 2.50\t\t Fairly Satisfactory\n";
        cout << "64.50 - 69.49%\t\t 2.75\t\t Fair\n";
        cout << "60.00 - 64.49%\t\t 3.00\t\t Passed\n";
        cout << "Below 60%\t\t 5.00\t\t Failed\033[0m\n";
        cout << "======================================================\n";

        double StoreGrade = 0;
        //for prelims, midterms, and prefinals
        if (Term == 1 || Term == 2 || Term == 3) {
            bool rest1 = true;
            bool rest1_2 = true;
            string pick1;

            bool rest2 = true;
            bool rest2_2 = true;
            string pick2;

            bool rest3 = true;
            bool rest3_2 = true;
            string pick3;

            bool rest4 = true;
            bool rest4_2 = true;
            string pick4;

            double PMPFGrade = 0;

            int numLQ = 0, numSQ = 0, numAT = 0, numExams = 0;
            double maxLongQuizScore = 0, maxShortQuizScore = 0, maxAssessmentTaskScore = 0, maxExamScore = 0;

            double totalLongQuizScore = 0.0;
            double totalShortQuizScore = 0.0;
            double totalAssessmentTaskScore = 0.0;
            double totalExamScore = 0.0;
            double totalmaxATscore = 0.0;
            double totalmaxLQscore = 0.0;
            double totalmaxSQscore = 0.0;
            double totalmaxExamscore = 0.0;

            double LQPercent = 25;
            double SQPercent = 15;
            double ATPercent = 10;
            double ExamPercent = 50;

            double show1 = 0;
            double show2 = 0;
            double show3 = 0;
            double show4 = 0;


            //for assessment task
            cout << "\n-Assessment Task(10%)";
            while (rest1) {

                cout << "\nHow many assessment tasks did you take on this subject: ";
                cin >> numAT;

                if (numAT == 0) {
                    cout << "You did not process any scores on your assessment tasks\n";
                    cout << endl;

                }
                else if (numAT != 0) {
                    for (int i = 0; i < numAT; i++) {
                        double score1;
                        cout << "Enter the score for assessment task #" << i + 1 << ": ";
                        cin >> score1;
                        totalAssessmentTaskScore += score1;
                        cout << "Enter how many items on this assessment task #" << i + 1 << ": ";
                        cin >> maxAssessmentTaskScore;

                        while (maxAssessmentTaskScore < score1) {
                            cout << "YOUR ITEMS SHOULD BE HIGHER THAN YOUR SCORE.\n";
                            cout << "Enter how many items on this assessment task #" << i + 1 << ": ";
                            cin >> maxAssessmentTaskScore;
                        }
                        cout << endl;
                        totalmaxATscore += maxAssessmentTaskScore;
                    }

                    show1 = (totalAssessmentTaskScore / totalmaxATscore) * ATPercent;

                }
                cin.ignore();

                cout << "Is this final? Type 'Yes' or 'yes to proceed,\n";
                cout << "or 'No' or 'no' to redo your scores.\n";
                while (rest1_2) {
                    cout << "Type your response here: ";
                    getline(cin, pick1);
                    if (pick1 == "Yes" || pick1 == "yes") {//proceeds to the next function
                        rest1_2 = false;
                        rest1 = false;
                    }
                    else if (pick1 == "No" || pick1 == "no") {//restarts to the previous loop
                        totalAssessmentTaskScore = 0;
                        totalmaxATscore = 0;
                        rest1 = true;
                        break;
                    }
                    else {
                        //if user type that is not given in the program it will generate an error message 
                        cout << "\nInvalid match. Pls Try Again!\n\n";
                        rest1_2 = true;
                    }

                }

            }

            cout << endl;
            if (numAT == 0) {
                cout << "Your assessment task grade will be automatically: \033[4m" << fixed << setprecision(2) << show1 << "%" << endl;
            }
            else if (numAT != 0) {
                cout << "Computation: (" << fixed << setprecision(0) << totalAssessmentTaskScore << " / " << totalmaxATscore << ")(0.1) = " << fixed << setprecision(2) << show1 << endl;
                cout << "Your total assessment task score is " << fixed << setprecision(0) << totalAssessmentTaskScore << "/" << totalmaxATscore << " which is equal to " << fixed << setprecision(2) << show1 << "%.\n";
            }

            cout << "\n======================================================\n";
            //for long quiz
            cout << "\n-Long Quiz(25%)";
            while (rest2) {

                cout << "\nHow many long quiz did you take on this subject: ";
                cin >> numLQ;

                if (numLQ == 0) {
                    cout << "You did not process any scores on your long quizzes\n";
                    cout << endl;
                }
                else if (numLQ != 0) {
                    for (int i = 0; i < numLQ; i++) {
                        double score2;
                        cout << "Enter the score for long quiz #" << i + 1 << ": ";
                        cin >> score2;
                        totalLongQuizScore += score2;
                        cout << "Enter how many items on this long quiz #" << i + 1 << ": ";
                        cin >> maxLongQuizScore;

                        while (maxLongQuizScore < score2) {
                            cout << "YOUR ITEMS SHOULD BE HIGHER THAN YOUR SCORE.\n";
                            cout << "Enter how many items on this long quiz #" << i + 1 << ": ";
                            cin >> maxLongQuizScore;
                        }
                        cout << endl;
                        totalmaxLQscore += maxLongQuizScore;
                    }

                    show2 = (totalLongQuizScore / totalmaxLQscore) * LQPercent;

                }
                cin.ignore();

                cout << "Is this final? Type 'Yes' or 'yes' to proceed,\n";
                cout << "or 'No' or 'no' to redo your scores.\n";
                while (rest2_2) {
                    cout << "Type your response here: ";
                    getline(cin, pick2);
                    if (pick2 == "Yes" || pick2 == "yes") {//proceeds to the next function
                        rest2_2 = false;
                        rest2 = false;
                    }
                    else if (pick2 == "No" || pick2 == "no") {//restarts to the previous loop
                        totalLongQuizScore = 0;
                        totalmaxLQscore = 0;
                        rest2 = true;
                        break;
                    }
                    else {
                        //if user type that is not given in the program it will generate an error message 
                        cout << "\nInvalid match. Pls Try Again!\n\n";
                        rest2_2 = true;
                    }

                }

            }

            cout << endl;
            if (numLQ == 0) {
                cout << "Your long quiz grade will be automatically: " << fixed << setprecision(2) << show2 << "%" << endl;
            }
            else if (numLQ != 0) {
                cout << "Computation: (" << fixed << setprecision(0) << totalLongQuizScore << " / " << totalmaxLQscore << ")(0.25) = " << fixed << setprecision(2) << show2 << endl;
                cout << "Your total long quiz score is " << fixed << setprecision(0) << totalLongQuizScore << "/" << totalmaxLQscore << " which is equal to " << fixed << setprecision(2) << show2 << "%.\n";
            }

            cout << "\n======================================================\n";
            //for short quiz
            cout << "\n-Short Quiz(15%)";
            while (rest3) {

                cout << "\nHow many short quiz did you take on this subject: ";
                cin >> numSQ;

                if (numSQ == 0) {
                    cout << "You did not process any scores on your short quizzes\n";
                    cout << endl;

                }
                else if (numSQ != 0) {
                    for (int i = 0; i < numSQ; i++) {
                        double score3;
                        cout << "Enter the score for short quiz #" << i + 1 << ": ";
                        cin >> score3;
                        totalShortQuizScore += score3;
                        cout << "Enter how many items on this short quiz #" << i + 1 << ": ";
                        cin >> maxShortQuizScore;

                        while (maxShortQuizScore < score3) {
                            cout << "YOUR ITEMS SHOULD BE HIGHER THAN YOUR SCORE.\n";
                            cout << "Enter how many items on this short quiz #" << i + 1 << ": ";
                            cin >> maxShortQuizScore;
                        }
                        cout << endl;
                        totalmaxSQscore += maxShortQuizScore;
                    }

                    show3 = (totalShortQuizScore / totalmaxSQscore) * SQPercent;

                }
                cin.ignore();

                cout << "Is this final? Type 'Yes' or 'yes' to proceed,\n";
                cout << "or 'No' or 'no' to redo your scores.\n";
                while (rest3_2) {
                    cout << "Type your response here: ";
                    getline(cin, pick3);
                    if (pick3 == "Yes" || pick3 == "yes") {//proceeds to the next function
                        rest3_2 = false;
                        rest3 = false;
                    }
                    else if (pick3 == "No" || pick3 == "no") {//restarts to the previous loop
                        totalShortQuizScore = 0;
                        totalmaxSQscore = 0;
                        rest3 = true;
                        break;
                    }
                    else {
                        //if user type that is not given in the program it will generate an error message 
                        cout << "\nInvalid match. Pls Try Again!\n\n";
                        rest3_2 = true;
                    }

                }

            }

            cout << endl;
            if (numSQ == 0) {
                cout << "Your short quiz grade will be automatically: " << fixed << setprecision(2) << show3 << "%" << endl;
            }
            else if (numSQ != 0) {
                cout << "Computation: (" << fixed << setprecision(0) << totalShortQuizScore << " / " << totalmaxSQscore << ")(0.15) = " << fixed << setprecision(2) << show3 << endl;
                cout << "Your total short quiz score is " << fixed << setprecision(0) << totalShortQuizScore << "/" << totalmaxSQscore << " which is equal to " << fixed << setprecision(2) << show3 << "%.\n";
            }

            cout << "\n======================================================\n";
            //for exam
            cout << "\n-Exam(50%)";
            while (rest4) {

                cout << "\nHow many exam did you take on this subject: ";
                cin >> numExams;

                if (numExams == 0) {
                    cout << "You did not process any scores on your exams\n";
                    cout << endl;
                }
                else if (numExams != 0) {
                    for (int i = 0; i < numExams; i++) {
                        double score4;
                        cout << "Enter the score for this exam #" << i + 1 << ": ";
                        cin >> score4;
                        totalExamScore += score4;
                        cout << "Enter how many items on this exam #" << i + 1 << ": ";
                        cin >> maxExamScore;

                        while (maxExamScore < score4) {
                            cout << "YOUR ITEMS SHOULD BE HIGHER THAN YOUR SCORE.\n";
                            cout << "Enter how many items on this exam #" << i + 1 << ": ";
                            cin >> maxExamScore;
                        }
                        cout << endl;
                        totalmaxExamscore += maxExamScore;
                    }

                    show4 = (totalExamScore / totalmaxExamscore) * ExamPercent;

                }
                cin.ignore();

                cout << "Is this final? Type 'Yes' or 'yes' to proceed,\n";
                cout << "or 'No' or 'no' to redo your scores.\n";
                while (rest4_2) {
                    cout << "Type your response here: ";
                    getline(cin, pick4);
                    if (pick4 == "Yes" || pick4 == "yes") {//proceeds to the next function
                        rest4_2 = false;
                        rest4 = false;
                    }
                    else if (pick4 == "No" || pick4 == "no") {//restarts to the previous loop
                        totalAssessmentTaskScore = 0;
                        totalmaxATscore = 0;
                        rest4 = true;
                        break;
                    }
                    else {
                        //if user type that is not given in the program it will generate an error message 
                        cout << "\nInvalid match. Pls Try Again!\n\n";
                        rest4_2 = true;
                    }

                }

            }

            cout << endl;
            if (numExams == 0) {
                cout << "Your exam grade will be automatically: " << fixed << setprecision(2) << show4 << "%" << endl;
            }
            else if (numExams != 0) {
                cout << "Computation: (" << fixed << setprecision(0) << totalExamScore << " / " << totalmaxExamscore << ")(0.5) = " << fixed << setprecision(2) << show4 << endl;
                cout << "Your total exam score is " << fixed << setprecision(0) << totalExamScore << "/" << totalmaxExamscore << " which is equal to " << fixed << setprecision(2) << show4 << "%.\n";
            }
            PMPFGrade = show1 + show2 + show3 + show4;

            cout << "\n\n======================================================\n\n";

            if (Term == 1) {
                //store prelimgrade here
                double PrelimGrade;
                double PrelimGradeEQ = 0;
                string PrelimDescription;
                PrelimGrade = PMPFGrade;

                cout << "Computation: " << show1 << " + " << show2 << " + " << show3 << " + " << show4 << " = " << PMPFGrade << "\n";
                cout << "Your Prelim grade on this subject is " << PrelimGrade << "\n";

                for (int i = 0; i < storeSizeSubjects; i++) {
                    if (storePrelim == storePrelimsSubjects[i]) {
                        storePrelimGrades[i] = PrelimGrade;
                        if (PrelimGrade >= 96.50 && PrelimGrade <= 100) {
                            storePrelimGradeEQ[i] = 1.00;
                            PrelimDescriptions[i] = "Excellent";
                            PrelimGradeEQ = storePrelimGradeEQ[i];
                            PrelimDescription = PrelimDescriptions[i];
                        }
                        else if (PrelimGrade >= 92.50 && PrelimGrade <= 96.49) {
                            storePrelimGradeEQ[i] = 1.25;
                            PrelimDescriptions[i] = "Superior";
                            PrelimGradeEQ = storePrelimGradeEQ[i];
                            PrelimDescription = PrelimDescriptions[i];
                        }
                        else if (PrelimGrade >= 88.50 && PrelimGrade <= 92.49) {
                            storePrelimGradeEQ[i] = 1.50;
                            PrelimDescriptions[i] = "Very Good";
                            PrelimGradeEQ = storePrelimGradeEQ[i];
                            PrelimDescription = PrelimDescriptions[i];
                        }
                        else if (PrelimGrade >= 84.50 && PrelimGrade <= 88.49) {
                            storePrelimGradeEQ[i] = 1.75;
                            PrelimDescriptions[i] = "Good";
                            PrelimGradeEQ = storePrelimGradeEQ[i];
                            PrelimDescription = PrelimDescriptions[i];
                        }
                        else if (PrelimGrade >= 79.50 && PrelimGrade <= 84.49) {
                            storePrelimGradeEQ[i] = 2.00;
                            PrelimDescriptions[i] = "Above Average";
                            PrelimGradeEQ = storePrelimGradeEQ[i];
                            PrelimDescription = PrelimDescriptions[i];
                        }
                        else if (PrelimGrade >= 74.50 && PrelimGrade <= 79.49) {
                            storePrelimGradeEQ[i] = 2.25;
                            PrelimDescriptions[i] = "Average";
                            PrelimGradeEQ = storePrelimGradeEQ[i];
                            PrelimDescription = PrelimDescriptions[i];
                        }
                        else if (PrelimGrade >= 69.50 && PrelimGrade <= 74.49) {
                            storePrelimGradeEQ[i] = 2.50;
                            PrelimDescriptions[i] = "Fairly Satisfactory";
                            PrelimGradeEQ = storePrelimGradeEQ[i];
                            PrelimDescription = PrelimDescriptions[i];
                        }
                        else if (PrelimGrade >= 64.50 && PrelimGrade <= 69.49) {
                            storePrelimGradeEQ[i] = 2.75;
                            PrelimDescriptions[i] = "Fair";
                            PrelimGradeEQ = storePrelimGradeEQ[i];
                            PrelimDescription = PrelimDescriptions[i];
                        }
                        else if (PrelimGrade >= 60.00 && PrelimGrade <= 64.49) {
                            storePrelimGradeEQ[i] = 3.00;
                            PrelimDescriptions[i] = "Passed";
                            PrelimGradeEQ = storePrelimGradeEQ[i];
                            PrelimDescription = PrelimDescriptions[i];
                        }
                        else {
                            storePrelimGradeEQ[i] = 5.00;
                            PrelimDescriptions[i] = "Failed";
                            PrelimGradeEQ = storePrelimGradeEQ[i];
                            PrelimDescription = PrelimDescriptions[i];
                        }

                    }

                }
                cout << "Your Prelim grade equivalent is: " << PrelimGradeEQ << "\n";
                cout << "Your Prelim grade description: " << PrelimDescription << "\n";
                cout << endl;
                cout << "======================================================\n\n";
            }
            else if (Term == 2) {
                //store midtermgrade here
                double MidtermGrade;
                double MidtermGradeEQ = 0;
                string MidtermDescription;
                MidtermGrade = PMPFGrade;

                cout << "Computation: " << show1 << " + " << show2 << " + " << show3 << " + " << show4 << " = " << PMPFGrade << "\n";
                cout << "Your Midterm grade on this subject is " << MidtermGrade << "\n";

                for (int i = 0; i < storeSizeSubjects; i++) {
                    if (storeMidterm == storeMidtermsSubjects[i]) {
                        storeMidtermGrades[i] = MidtermGrade;
                        if (MidtermGrade >= 96.50 && MidtermGrade <= 100) {
                            storeMidtermGradeEQ[i] = 1.00;
                            MidtermDescriptions[i] = "Excellent";
                            MidtermGradeEQ = storeMidtermGradeEQ[i];
                            MidtermDescription = MidtermDescriptions[i];
                        }
                        else if (MidtermGrade >= 92.50 && MidtermGrade <= 96.49) {
                            storeMidtermGradeEQ[i] = 1.25;
                            MidtermDescriptions[i] = "Superior";
                            MidtermGradeEQ = storeMidtermGradeEQ[i];
                            MidtermDescription = MidtermDescriptions[i];
                        }
                        else if (MidtermGrade >= 88.50 && MidtermGrade <= 92.49) {
                            storeMidtermGradeEQ[i] = 1.50;
                            MidtermDescriptions[i] = "Very Good";
                            MidtermGradeEQ = storeMidtermGradeEQ[i];
                            MidtermDescription = MidtermDescriptions[i];
                        }
                        else if (MidtermGrade >= 84.50 && MidtermGrade <= 88.49) {
                            storeMidtermGradeEQ[i] = 1.75;
                            MidtermDescriptions[i] = "Good";
                            MidtermGradeEQ = storeMidtermGradeEQ[i];
                            MidtermDescription = MidtermDescriptions[i];
                        }
                        else if (MidtermGrade >= 79.50 && MidtermGrade <= 84.49) {
                            storeMidtermGradeEQ[i] = 2.00;
                            MidtermDescriptions[i] = "Above Average";
                            MidtermGradeEQ = storeMidtermGradeEQ[i];
                            MidtermDescription = MidtermDescriptions[i];
                        }
                        else if (MidtermGrade >= 74.50 && MidtermGrade <= 79.49) {
                            storeMidtermGradeEQ[i] = 2.25;
                            MidtermDescriptions[i] = "Average";
                            MidtermGradeEQ = storeMidtermGradeEQ[i];
                            MidtermDescription = MidtermDescriptions[i];
                        }
                        else if (MidtermGrade >= 69.50 && MidtermGrade <= 74.49) {
                            storeMidtermGradeEQ[i] = 2.50;
                            MidtermDescriptions[i] = "Fairly Satisfactory";
                            MidtermGradeEQ = storeMidtermGradeEQ[i];
                            MidtermDescription = MidtermDescriptions[i];
                        }
                        else if (MidtermGrade >= 64.50 && MidtermGrade <= 69.49) {
                            storeMidtermGradeEQ[i] = 2.75;
                            MidtermDescriptions[i] = "Fair";
                            MidtermGradeEQ = storeMidtermGradeEQ[i];
                            MidtermDescription = MidtermDescriptions[i];
                        }
                        else if (MidtermGrade >= 60.00 && MidtermGrade <= 64.49) {
                            storeMidtermGradeEQ[i] = 3.00;
                            MidtermDescriptions[i] = "Passed";
                            MidtermGradeEQ = storeMidtermGradeEQ[i];
                            MidtermDescription = MidtermDescriptions[i];
                        }
                        else {
                            storeMidtermGradeEQ[i] = 5.00;
                            MidtermDescriptions[i] = "Failed";
                            MidtermGradeEQ = storeMidtermGradeEQ[i];
                            MidtermDescription = MidtermDescriptions[i];
                        }

                    }

                }

                cout << "Your Midterm grade equivalent is: " << MidtermGradeEQ << "\n";
                cout << "Your Midterm grade description: " << MidtermDescription << "\n";
                cout << endl;
                cout << "======================================================\n\n";
            }
            else if (Term == 3) {
                //store prefinalgrade here
                double PrefinalGrade;
                double PrefinalGradeEQ = 0;
                string PrefinalDescription;
                PrefinalGrade = PMPFGrade;

                cout << "Computation: " << show1 << " + " << show2 << " + " << show3 << " + " << show4 << " = " << PMPFGrade << "\n";
                cout << "Your Prefinal grade on this subject is " << PrefinalGrade << "\n";

                for (int i = 0; i < storeSizeSubjects; i++) {
                    if (storePrefinal == storePrefinalsSubjects[i]) {
                        storePrefinalGrades[i] = PrefinalGrade;
                        if (PrefinalGrade >= 96.50 && PrefinalGrade <= 100) {
                            storePrefinalGradeEQ[i] = 1.00;
                            PrefinalDescriptions[i] = "Excellent";
                            PrefinalGradeEQ = storePrefinalGradeEQ[i];
                            PrefinalDescription = PrefinalDescriptions[i];
                        }
                        else if (PrefinalGrade >= 92.50 && PrefinalGrade <= 96.49) {
                            storePrefinalGradeEQ[i] = 1.25;
                            PrefinalDescriptions[i] = "Superior";
                            PrefinalGradeEQ = storePrefinalGradeEQ[i];
                            PrefinalDescription = PrefinalDescriptions[i];
                        }
                        else if (PrefinalGrade >= 88.50 && PrefinalGrade <= 92.49) {
                            storePrefinalGradeEQ[i] = 1.50;
                            PrefinalDescriptions[i] = "Very Good";
                            PrefinalGradeEQ = storePrefinalGradeEQ[i];
                            PrefinalDescription = PrefinalDescriptions[i];
                        }
                        else if (PrefinalGrade >= 84.50 && PrefinalGrade <= 88.49) {
                            storePrefinalGradeEQ[i] = 1.75;
                            PrefinalDescriptions[i] = "Good";
                            PrefinalGradeEQ = storePrefinalGradeEQ[i];
                            PrefinalDescription = PrefinalDescriptions[i];
                        }
                        else if (PrefinalGrade >= 79.50 && PrefinalGrade <= 84.49) {
                            storePrefinalGradeEQ[i] = 2.00;
                            PrefinalDescriptions[i] = "Above Average";
                            PrefinalGradeEQ = storePrefinalGradeEQ[i];
                            PrefinalDescription = PrefinalDescriptions[i];
                        }
                        else if (PrefinalGrade >= 74.50 && PrefinalGrade <= 79.49) {
                            storePrefinalGradeEQ[i] = 2.25;
                            PrefinalDescriptions[i] = "Average";
                            PrefinalGradeEQ = storePrefinalGradeEQ[i];
                            PrefinalDescription = PrefinalDescriptions[i];
                        }
                        else if (PrefinalGrade >= 69.50 && PrefinalGrade <= 74.49) {
                            storePrefinalGradeEQ[i] = 2.50;
                            PrefinalDescriptions[i] = "Fairly Satisfactory";
                            PrefinalGradeEQ = storePrefinalGradeEQ[i];
                            PrefinalDescription = PrefinalDescriptions[i];
                        }
                        else if (PrefinalGrade >= 64.50 && PrefinalGrade <= 69.49) {
                            storePrefinalGradeEQ[i] = 2.75;
                            PrefinalDescriptions[i] = "Fair";
                            PrefinalGradeEQ = storePrefinalGradeEQ[i];
                            PrefinalDescription = PrefinalDescriptions[i];
                        }
                        else if (PrefinalGrade >= 60.00 && PrefinalGrade <= 64.49) {
                            storePrefinalGradeEQ[i] = 3.00;
                            PrefinalDescriptions[i] = "Passed";
                            PrefinalGradeEQ = storePrefinalGradeEQ[i];
                            PrefinalDescription = PrefinalDescriptions[i];
                        }
                        else {
                            storePrefinalGradeEQ[i] = 5.00;
                            PrefinalDescriptions[i] = "Failed";
                            PrefinalGradeEQ = storePrefinalGradeEQ[i];
                            PrefinalDescription = PrefinalDescriptions[i];
                        }

                    }

                }

                cout << "Your Prefinal grade equivalent is: " << PrefinalGradeEQ << "\n";
                cout << "Your Prefinal grade description: " << PrefinalDescription << "\n";
                cout << endl;
                cout << "======================================================\n\n";

            }
        }
        else if (Term == 4) {
            //for final grade
            bool rest1 = true;
            bool rest2 = true;
            double FinalGradeEQ = 0;
            string FinalDescription;
            string pick;

            cout << endl;
            double PrelimGrade, MidtermGrade, PrefinalGrade, PrelimScore, MidtermScore, PrefinalScore, FinalGrade;

            while (rest1) {
                cout << "What is your Grade on this Subject in Prelims: ";
                cin >> PrelimGrade;
                cout << "What is your Grade on this Subject in Midterms: ";
                cin >> MidtermGrade;
                cout << "What is your Grade on this Subject in Prefinals: ";
                cin >> PrefinalGrade;
                cin.ignore();

                cout << endl;
                cout << "Are these your final grades? Type 'Yes' or 'yes' to proceed,\n";
                cout << "or 'No' or 'no' to redo your subjects.\n";
                while (rest2) {
                    cout << "Type your response here: ";
                    getline(cin, pick);
                    if (pick == "Yes" || pick == "yes") {//proceeds to the next function
                        rest2 = false;
                        rest1 = false;
                        cout << endl;
                    }
                    else if (pick == "No" || pick == "no") {//restarts to the previous loop
                        cout << endl;
                        rest1 = true;
                        break;
                    }
                    else {
                        //if user type that is not given in the program it will generate an error message 
                        cout << endl;
                        cout << "Invalid match. Please Try Again!\n";
                        rest2 = true;
                    }

                }

            }

            PrelimScore = PrelimGrade * 0.3;
            MidtermScore = MidtermGrade * 0.3;
            PrefinalScore = PrefinalGrade * 0.4;

            FinalGrade = PrelimScore + MidtermScore + PrefinalScore;

            cout << "======================================================\n\n";

            cout << "Computation: " << PrelimGrade << "(0.3) + " << MidtermGrade << "\(0.3) + " << PrefinalGrade << "(0.4) = " << fixed << setprecision(2) << FinalGrade << "\n";
            cout << "Your Final grade in this subject is: " << fixed << setprecision(2) << FinalGrade << "\n";

            for (int i = 0; i < storeSizeSubjects; i++) {
                if (storeFinal == storeFinalsSubjects[i]) {
                    storeFinalGrades[i] = FinalGrade;

                    if (FinalGrade >= 96.50 && FinalGrade <= 100) {
                        storeFinalGradeEQ[i] = 1.00;
                        FinalDescriptions[i] = "Excellent";
                        FinalGradeEQ = storeFinalGradeEQ[i];
                        FinalDescription = FinalDescriptions[i];
                    }
                    else if (FinalGrade >= 92.50 && FinalGrade <= 96.49) {
                        storeFinalGradeEQ[i] = 1.25;
                        FinalDescriptions[i] = "Superior";
                        FinalGradeEQ = storeFinalGradeEQ[i];
                        FinalDescription = FinalDescriptions[i];
                    }
                    else if (FinalGrade >= 88.50 && FinalGrade <= 92.49) {
                        storeFinalGradeEQ[i] = 1.50;
                        FinalDescriptions[i] = "Very Good";
                        FinalGradeEQ = storeFinalGradeEQ[i];
                        FinalDescription = FinalDescriptions[i];
                    }
                    else if (FinalGrade >= 84.50 && FinalGrade <= 88.49) {
                        storeFinalGradeEQ[i] = 1.75;
                        FinalDescriptions[i] = "Good";
                        FinalGradeEQ = storeFinalGradeEQ[i];
                        FinalDescription = FinalDescriptions[i];
                    }
                    else if (FinalGrade >= 79.50 && FinalGrade <= 84.49) {
                        storeFinalGradeEQ[i] = 2.00;
                        FinalDescriptions[i] = "Above Average";
                        FinalGradeEQ = storeFinalGradeEQ[i];
                        FinalDescription = FinalDescriptions[i];
                    }
                    else if (FinalGrade >= 74.50 && FinalGrade <= 79.49) {
                        storeFinalGradeEQ[i] = 2.25;
                        FinalDescriptions[i] = "Average";
                        FinalGradeEQ = storeFinalGradeEQ[i];
                        FinalDescription = FinalDescriptions[i];
                    }
                    else if (FinalGrade >= 69.50 && FinalGrade <= 74.49) {
                        storeFinalGradeEQ[i] = 2.50;
                        FinalDescriptions[i] = "Fairly Satisfactory";
                        FinalGradeEQ = storeFinalGradeEQ[i];
                        FinalDescription = FinalDescriptions[i];
                    }
                    else if (FinalGrade >= 64.50 && FinalGrade <= 69.49) {
                        storeFinalGradeEQ[i] = 2.75;
                        FinalDescriptions[i] = "Fair";
                        FinalGradeEQ = storeFinalGradeEQ[i];
                        FinalDescription = FinalDescriptions[i];
                    }
                    else if (FinalGrade >= 60.00 && FinalGrade <= 64.49) {
                        storeFinalGradeEQ[i] = 3.00;
                        FinalDescriptions[i] = "Passed";
                        FinalGradeEQ = storeFinalGradeEQ[i];
                        FinalDescription = FinalDescriptions[i];
                    }
                    else {
                        storeFinalGradeEQ[i] = 5.00;
                        FinalDescriptions[i] = "Failed";
                        FinalGradeEQ = storeFinalGradeEQ[i];
                        FinalDescription = FinalDescriptions[i];
                    }

                }

            }
            cout << "Your Final grade equivalent is: " << FinalGradeEQ << "\n";
            cout << "Your Final grade description: " << FinalDescription << "\n";
            cout << endl;
            cout << "======================================================\n\n";

        }
    }

    void DispResults() {//a function used to display the computated grades, the grades will be generated in a file and will be opend automatically
        //but it is only limited to windows platform
        int pick;
        int pick2;
        string pick3;
        bool res = true;

        while (res) {
            bool rest = true;
            cout << "Note: You will never process anymore subjects if you want to check your grades!\n";
            cout << "Type 1 or 2\n";
            cout << "[1] - Checking of your grades\n";
            cout << "[2] - Process another subject\n";
            cout << "Type your response here: ";
            cin >> pick;
            cin.ignore();
            if (pick == 1) {
                while (rest) {
                    bool rest2 = true;
                    cout << endl;
                    cout << "What grades do you want to check? (You will type a number 1 - 5 to generate your grade\n";
                    cout << "and this will open a file automatically)\n";
                    cout << "[1] - Prelims\n[2] - Midterms\n[3] - Pre-finals\n[4] - Finals\n[5] - All Grades\n";
                    cout << "Type your response here: ";
                    cin >> pick2;
                    cin.ignore();
                    bool validPick2 = false;
                    if (pick2 == 1) {
                        ofstream prelimGradesFile("prelimgrades.txt", ios::out);
                        if (prelimGradesFile.is_open()) {
                            prelimGradesFile << left << setw(60) << "Prelims" << setw(20) << "Grades" << setw(30) << "Grade Equivalent" << "Description" << endl;
                            if (prelimSubs == 0) {
                                prelimGradesFile << "*You did not process any subjects on this term!";
                            }
                            for (int i = 0; i < prelimSubs; i++) {
                                if (!storePrelimsSubjects[i].empty()) {
                                    prelimGradesFile << left << setw(60) << storePrelimsSubjects[i] << setw(20) << fixed << setprecision(2) << storePrelimGrades[i] << setw(30) << storePrelimGradeEQ[i] << PrelimDescriptions[i] << endl;
                                }

                            }
                            cout << "Grades and Subjects written in prelimgrades.txt successfully.\n\n";
                            prelimGradesFile.close();
                        }
                        else {
                            cout << "The file can't be opened.";
                            return;
                        }
#ifdef _WIN32
                        //windows platform
                        system("start prelimgrades.txt");

#endif
                        validPick2 = true;
                    }
                    else if (pick2 == 2) {
                        ofstream midtermGradesFile("midtermgrades.txt", ios::out);
                        if (midtermGradesFile.is_open()) {
                            midtermGradesFile << left << setw(60) << "Midterms" << setw(20) << "Grades" << setw(30) << "Grade Equivalent" << "Description" << endl;
                            if (midtermSubs == 0) {
                                midtermGradesFile << "*You did not process any subjects on this term!";
                            }
                            for (int j = 0; j < midtermSubs; j++) {
                                if (!storeMidtermsSubjects[j].empty()) {
                                    midtermGradesFile << left << setw(60) << storeMidtermsSubjects[j] << setw(20) << fixed << setprecision(2) << storeMidtermGrades[j] << setw(30) << storeMidtermGradeEQ[j] << MidtermDescriptions[j] << endl;
                                }

                            }
                            cout << "\nGrades and Subjects written in midtermgrades.txt successfully.\n\n";
                            midtermGradesFile.close();
                        }
                        else {
                            cout << "The file can't be opened.";
                            return;
                        }
#ifdef _WIN32
                        //windows platform
                        system("start midtermgrades.txt");

#endif
                        validPick2 = true;
                    }
                    else if (pick2 == 3) {
                        ofstream prefinalGradesFile("prefinalgrades.txt", ios::out);
                        if (prefinalGradesFile.is_open()) {
                            prefinalGradesFile << left << setw(60) << "Prefinals" << setw(20) << "Grades" << setw(30) << "Grade Equivalent" << "Description" << endl;
                            if (prefinalSubs == 0) {
                                prefinalGradesFile << "*You did not process any subjects on this term!";
                            }
                            for (int k = 0; k < prefinalSubs; k++) {
                                if (!storePrefinalsSubjects[k].empty()) {
                                    prefinalGradesFile << left << setw(60) << storePrefinalsSubjects[k] << setw(20) << fixed << setprecision(2) << storePrefinalGrades[k] << setw(30) << storePrefinalGradeEQ[k] << PrefinalDescriptions[k] << endl;
                                }

                            }
                            cout << "\nGrades and Subjects written in prefinalgrades.txt successfully.\n\n";
                            prefinalGradesFile.close();
                        }
                        else {
                            cout << "The file can't be opened.";
                            return;
                        }
#ifdef _WIN32
                        //windows platform
                        system("start prefinalgrades.txt");

#endif
                    }
                    else if (pick2 == 4) {
                        ofstream finalGradesFile("finalgrades.txt", ios::out);
                        if (finalGradesFile.is_open()) {
                            finalGradesFile << left << setw(60) << "Finals" << setw(20) << "Grades" << setw(30) << "Grade Equivalent" << "Description" << endl;
                            if (finalSubs == 0) {
                                finalGradesFile << "*You did not process any subjects on this term!";
                            }
                            for (int l = 0; l < finalSubs; l++) {
                                if (!storeFinalsSubjects[l].empty()) {
                                    finalGradesFile << left << setw(60) << storeFinalsSubjects[l] << setw(20) << fixed << setprecision(2) << storeFinalGrades[l] << setw(30) << storeFinalGradeEQ[l] << FinalDescriptions[l] << endl;
                                }

                            }
                            cout << "\nGrades and Subjects written in finalgrades.txt successfully.\n\n";
                            finalGradesFile.close();
                        }
                        else {
                            cout << "The file can't be opened.";
                            return;
                        }
#ifdef _WIN32
                        //windows platform
                        system("start finalgrades.txt");

#endif
                        validPick2 = true;
                    }
                    else if (pick2 == 5) {
                        ofstream allGradesFile("allGrades.txt", ios::out);
                        if (allGradesFile.is_open()) {
                            allGradesFile << left << setw(60) << "Prelims" << setw(20) << "Grades" << setw(30) << "Grade Equivalent" << "Description" << endl;
                            if (prelimSubs == 0) {
                                allGradesFile << "*You did not process any subjects on this term!";
                            }
                            for (int i = 0; i < prelimSubs; i++) {
                                if (!storePrelimsSubjects[i].empty()) {
                                    allGradesFile << left << setw(60) << storePrelimsSubjects[i] << setw(20) << fixed << setprecision(2) << storePrelimGrades[i] << setw(30) << storePrelimGradeEQ[i] << PrelimDescriptions[i] << endl;
                                }

                            }
                            allGradesFile << "\n\n";

                            allGradesFile << left << setw(60) << "Midterms" << setw(20) << "Grades" << setw(30) << "Grade Equivalent" << "Description" << endl;
                            if (midtermSubs == 0) {
                                allGradesFile << "*You did not process any subjects on this term!";
                            }
                            for (int j = 0; j < midtermSubs; j++) {
                                if (!storeMidtermsSubjects[j].empty()) {
                                    allGradesFile << left << setw(60) << storeMidtermsSubjects[j] << setw(20) << fixed << setprecision(2) << storeMidtermGrades[j] << setw(30) << storeMidtermGradeEQ[j] << MidtermDescriptions[j] << endl;
                                }

                            }
                            allGradesFile << "\n\n";

                            allGradesFile << left << setw(60) << "Prefinals" << setw(20) << "Grades" << setw(30) << "Grade Equivalent" << "Description" << endl;
                            if (prefinalSubs == 0) {
                                allGradesFile << "*You did not process any subjects on this term!";
                            }
                            for (int k = 0; k < prefinalSubs; k++) {
                                if (!storePrefinalsSubjects[k].empty()) {
                                    allGradesFile << left << setw(60) << storePrefinalsSubjects[k] << setw(20) << fixed << setprecision(2) << storePrefinalGrades[k] << setw(30) << storePrefinalGradeEQ[k] << PrefinalDescriptions[k] << endl;
                                }

                            }
                            allGradesFile << "\n\n";

                            allGradesFile << left << setw(60) << "Finals" << setw(20) << "Grades" << setw(30) << "Grade Equivalent" << "Description" << endl;
                            if (finalSubs == 0) {
                                allGradesFile << "*You did not process any subjects on this term!";
                            }
                            for (int l = 0; l < finalSubs; l++) {
                                if (!storeFinalsSubjects[l].empty()) {
                                    allGradesFile << left << setw(60) << storeFinalsSubjects[l] << setw(20) << fixed << setprecision(2) << storeFinalGrades[l] << setw(30) << storeFinalGradeEQ[l] << FinalDescriptions[l] << endl;
                                }

                            }

                            cout << "\nGrades and Subjects written in allGrades.txt successfully.\n\n";
                            allGradesFile.close();

                        }
                        else {
                            cout << "The file can't be opened.";
                            return;
                        }
#ifdef _WIN32
                        //windows platform
                        system("start allGrades.txt");

#endif
                        validPick2 = true;
                    }
                    else {
                        cout << endl;
                        cout << "You did not type any of the given numbers. Try again.";
                        rest = true;
                        continue;
                    }

                    cout << "Would you like to check your other grades? Type 'Yes' or 'yes' to proceed,\n";
                    cout << "or 'No' or 'no' to finish processing your subjects.\n";
                    while (rest2) {
                        cout << "Type your response here: ";
                        getline(cin, pick3);
                        if (pick3 == "Yes" || pick3 == "yes") {
                            rest = true;
                            break;
                        }
                        else if (pick3 == "No" || pick3 == "no") {
                            cout << endl;
                            cout << "**Thank you for using our system, we are open for suggestions and criticisms!\n";
                            exit(0);
                        }
                        else {
                            cout << endl;
                            cout << "Invalid Match. Try Again\n\n";
                            rest2 = true;
                        }
                    }


                }
                res = false;
            }
            else if (pick == 2) {
                if (countSub >= storeSizeSubjects) {
                    cout << endl;
                    cout << "You have no more subjects to process!\n\n";
                    res = true;
                }
                else {
                    DispSubjects();
                    InpProcessSubject();
                    PerformScoresOP();
                    DispResults();
                }

            }
            else {
                cout << "\n";
                cout << "Invalid match. Try Again!\n";
                DispResults();
            }

        }
    }

};

int main() {
    StudentRMSystem system;

    cout << "----------[STUDENT REPORT MANAGEMENT SYSTEM]----------\n\n";
    cout << "======================================================\n\n";
    cout << "Note:(IMPORTANT)\n";
    cout << "Please enter the right input or it may cause the program terminate abnormally,\n there will be guidelines that will help you.\n\n";
    cout << "There will be times that you will be asked to enter numbers,\n do not enter letters and character symbols on that given statement,\n";
    cout << " or the code will terminate abnormally\n\n";
    cout << "======================================================\n\n";
    system.InpSubjects();
    system.RestSubjects();
    system.DispSubjects();
    system.InpProcessSubject();
    system.PerformScoresOP();
    system.DispResults();

    return 0;
}
