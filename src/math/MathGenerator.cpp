#include "MathGenerator.h"

#include <Arduino.h>

Question MathGenerator::generateEasyQuestion() {

    Question q;

    q.num1 = random(1, 10);

    q.num2 = random(1, 10);

    q.operation = '+';

    q.correctAnswer = q.num1 + q.num2;

    q.correctIndex = random(0, 3);

    int wrong1 = q.correctAnswer + random(1, 5);

    int wrong2 = q.correctAnswer - random(1, 5);

    int wrongCounter = 0;

    for(int i = 0; i < 3; i++) {

        if(i == q.correctIndex) {

            q.options[i] = q.correctAnswer;
        }
        else {

            if(wrongCounter == 0) {

                q.options[i] = wrong1;
            }
            else {

                q.options[i] = wrong2;
            }

            wrongCounter++;
        }
    }
    

    return q;
}

Question MathGenerator::generateSubtractionQuestion() {

    Question q;

    q.num1 = random(5, 20);

    q.num2 = random(1, q.num1);

    q.operation = '-';

    q.correctAnswer = q.num1 - q.num2;

    q.correctIndex = random(0, 3);

    for(int i = 0; i < 3; i++) {

        if(i == q.correctIndex) {

            q.options[i] = q.correctAnswer;
        }
        else {

            int wrongAnswer;

            do {

                wrongAnswer =
                    q.correctAnswer + random(-5, 6);

            } while(
                wrongAnswer == q.correctAnswer
            );

            q.options[i] = wrongAnswer;
        }
    }

    return q;
}

Question MathGenerator::generateWallQuestion() {

    Question q;

    bool multiplication = random(0, 2);

    if(multiplication) {

        q.num1 = random(2, 10);
        q.num2 = random(2, 10);

        q.operation = '*';

        q.correctAnswer =
            q.num1 * q.num2;
    }
    else {

        q.num2 = random(2, 10);

        q.correctAnswer =
            random(2, 10);

        q.num1 =
            q.correctAnswer * q.num2;

        q.operation = '/';
    }

    q.correctIndex = random(0, 3);

    int wrongCount = 0;

    for(int i=0;i<3;i++) {

        if(i == q.correctIndex) {

            q.options[i] =
                q.correctAnswer;
        }
        else {

            int wrong;

            do {

                wrong =
                    q.correctAnswer +
                    random(-8,9);

            } while(
                wrong == q.correctAnswer
            );

            q.options[i] = wrong;

            wrongCount++;
        }
    }

    return q;
}