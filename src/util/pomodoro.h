#ifndef POMODORO_H
#define POMODORO_H

#include <QObject>
#include <QTimer>
#include "configuration.h"

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

    void startIntegration();

    static QString roundToString(Round round);

    static const int defaultTimeWork = 25;
    static const int defaultTimeShortBreak = 5;
    static const int defaultTimeLongBreak = 15;
    static const int defaultWorkRounds = 4;
    static const QStringList allConfigs;

    void loadConfig(Configuration& config);
    void saveConfig(Configuration& config);

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
    void updateConfig(bool shouldUpdateRound);

signals:
    void updateTimer(int remainaing, int total);
    void updateRound(Round round, int runnedRound, int workRound);
    void updateState(State state);

public slots:
    void start();
    void pause();
    void resume();
    void stop();
    void resetTimer();

    int getConfig(int index);
    void setConfig(int index, int value);

private slots:
    void intervalUpdate();
};

#endif // POMODORO_H
