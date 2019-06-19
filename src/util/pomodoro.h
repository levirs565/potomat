#ifndef POMODORO_H
#define POMODORO_H

#include <QObject>
#include <QTimer>

class Pomodoro : public QObject
{
    Q_OBJECT
public:
    enum Round {
        Work,
        ShortBreak,
        LongBreak
    };

    enum State {
        Started,
        Paused,
        Idle
    };

    explicit Pomodoro(QObject *parent = nullptr);

    static QString roundToString(Round round);

private:
    QTimer *mTimer;
    Round mCurrentRound;
    State mCurrentState;
    int mCurrentTotal;
    int mCurrentRemaining;
    int mRound;
    int mWorkRounds;
    int mTimeWork;
    int mTimeShortBreak;
    int mTimeLongBreak;

    void switchRound(Round round);
    void switchState(State state);
    void callUpdateTimer();
    void reset();

signals:
    void updateTimer(int remainaing, int total);
    void updateRound(Round round, int runnedRound);
    void updateState(State state);

public slots:
    void start();
    void pause();
    void resume();
    void stop();

private slots:
    void intervalUpdate();
};

#endif // POMODORO_H