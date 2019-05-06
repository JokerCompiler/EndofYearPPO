#ifndef EXERCISE_H
#define EXERCISE_H

#include <QString>
#include <vector>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include <QLineEdit>
#include <QTextEdit>
#include <QTime>
#include <QCoreApplication>
#define BEGINOFEXER ("Commencer la série d'exercises")
#define ENDOFEXER ("Fin de la série")
#define NEXTOFEXER ("Prochaine question")
#define CHECKOFEXER ("Valider")
#define ZEROEXER ("Recommencer")


struct Question{
    QString htmlText;
    QString Answer;
    QString AnswerLabel;
    QString Answer_SbS;
};
class Exercise{

public:


    Exercise(QVector<Question> qrc2, QLineEdit * Exer_Input, QTextEdit * Exer_RichText,
    QLabel * Exer_QuestionNum, QLabel * Exer_Recherche, QPushButton * Exer_NextBtn, QPushButton * Exer_Reset){
        QVector<Question> qrc = qrc2;
        _exercice.questions = qrc;
        _exercice.Length = qrc.length();
        _exercice.Level = 0;
        this->Exer_Input = Exer_Input;
        this->Exer_RichText = Exer_RichText;
        this->Exer_QuestionNum = Exer_QuestionNum;
        this->Exer_Recherche = Exer_Recherche;
        this->Exer_NextBtn = Exer_NextBtn;
        this->Exer_Reset = Exer_Reset;
    }
    void ChangeInputState(bool state){
        Exer_Input->setEnabled(state);
        Exer_QuestionNum->setEnabled(state);
        Exer_Recherche->setEnabled(state);
        Exer_Reset->setEnabled(state);
    }
    void LoadContent(int flag = NEXT){
        switch (flag) {
        case REFRESH:
            {
            ChangeInputState(false);
            Exer_NextBtn->setText(BEGINOFEXER);
            }
            break;
        case CORRECT:
            {
                ChangeInputState(true);
                Exer_RichText->setText(Exer_RichText->toHtml() + "\nBonne réponse!\n ");
                if(_exercice.Level >= (_exercice.Length-1) ){
                    Exer_NextBtn->setText(ENDOFEXER);
                }else{
                ChangeInputState(false);
                Exer_NextBtn->setText(NEXTOFEXER);
                }
            }
            break;
        case FALSE:
            {
                ChangeInputState(true);
                Exer_RichText->setText(Exer_RichText->toHtml() + "\nMauvaise réponse!\n " + _exercice.questions[_exercice.Level].Answer_SbS);
                if(_exercice.Level >= (_exercice.Length-1)){
                    Exer_NextBtn->setText(ENDOFEXER);
                }else{
                ChangeInputState(false);
                Exer_NextBtn->setText(NEXTOFEXER);
                }
            }
            break;
        case NEXT:
            {
            ChangeInputState(true);
            Question newQuestion = _exercice.questions[_exercice.Level];
            Exer_Input->setText("");
            Exer_RichText->setHtml(newQuestion.htmlText);
            Exer_Recherche->setText(newQuestion.AnswerLabel);
            Exer_QuestionNum->setText(_exercice.WhereAt);
            Exer_NextBtn->setText(CHECKOFEXER);
            }
            break;
        case END:
            {
            ChangeInputState(false);
            Exer_RichText->setHtml("newQuestion.htmlText""");
            Exer_NextBtn->setText(ZEROEXER);
            }
            break;
        }

    }
    void CheckAnswer(){
        if(Exer_Input->text() != _exercice.questions[_exercice.Level].Answer){
            LoadContent(FALSE);
        }else{
            LoadContent(CORRECT);
        }
    }

    int getState(){
        return _exercice.BtnState;
    }
    void FirstQuestion(){
        LoadContent(REFRESH);
    }
    void NextQuestion(){
        if(Exer_NextBtn->text() == CHECKOFEXER){
            delay2(20);
            CheckAnswer();
            return;
        }
        if(Exer_NextBtn->text() == ZEROEXER){
            delay2(20);
            Reset();
            return;
        }
        if(Exer_NextBtn->text() == ENDOFEXER){
            delay2(20);
            LoadContent(END);
            return;
        }
        if(Exer_NextBtn->text() == NEXTOFEXER){
            delay2(20);
                _exercice.Level = _exercice.Level + 1;
                if(_exercice.Level == _exercice.Length){
                    Exer_NextBtn->setText(ENDOFEXER);
                    return;
                }
                _exercice.WhereAt = "Question " + QString::number(_exercice.Level+1) + "/" + QString::number(_exercice.Length);
                ChangeInputState(true);
                LoadContent();
            return;
        }
        if(Exer_NextBtn->text() == BEGINOFEXER){
            delay2(20);
            ChangeInputState(true);
            _exercice.WhereAt = "Question " + QString::number(_exercice.Level+1) + "/" + QString::number(_exercice.Length);
            LoadContent();
            return;
        }
    }

    void Reset(){
        Exer_Input->setText("");
        _exercice.Level = 0;
        _exercice.WhereAt = "Question " + QString::number(_exercice.Level+1) + "/" + QString::number(_exercice.Length);
        ChangeInputState(false);
        Exercise(_exercice.questions,Exer_Input,Exer_RichText,Exer_QuestionNum,Exer_Recherche, Exer_NextBtn, Exer_Reset);
        LoadContent(REFRESH);
    }

private:
    void delay2( int millisecondsToWait )
    {
        QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
        while( QTime::currentTime() < dieTime )
        {
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
        }
    }
    enum btnState {NEW, CORRECT, FALSE, NEXT,END, REFRESH};
    struct Exer{
        QVector<Question> questions;
        QString WhereAt;
        int Level;
        int Length;
        btnState BtnState;
    };
    QPushButton * Exer_NextBtn;
    QPushButton * Exer_Reset;
    QLineEdit * Exer_Input;
    QTextEdit * Exer_RichText;
    QLabel * Exer_QuestionNum;
    QLabel * Exer_Recherche;
    Exer _exercice = {};

};
#endif // EXERCISE_H
