#include "pomodoro.h"
#include <QDebug>

Pomodoro::Pomodoro(QObject *parent)
    : QObject(parent),
      mTimer(new QTimer(this)),
      mCurrentState(Idle),
      mRound(0),
      mWorkRounds(1),
      mTimeWork(1),
      mTimeShortBreak(1),
      mTimeLongBreak(1)
{
    connect(mTimer, SIGNAL(timeout()), this, SLOT(intervalUpdate()));
}

void Pomodoro::startIntegration()
{
    switchRound(Work);
}

void Pomodoro::start()
{
    if (mCurrentState != Idle)
        throw "Cannot start when not idle";

    reset();
    switchRound(Work);
    mTimer->start(1000);
    switchState(Started);
}

void Pomodoro::pause()
{
    if (mCurrentState != Started)
        throw "Cannot pause when not started";

    mTimer->stop();
    switchState(Paused);
}

void Pomodoro::resume()
{
    if (mCurrentState != Paused)
        throw "Cannot resume when not paused";

    mTimer->start(1000);
    switchState(Started);
}

void Pomodoro::stop()
{
    if (mCurrentState != Started)
        throw "Cannot stop when not started";

    mTimer->stop();
    reset();
    switchState(Idle);
}

void Pomodoro::resetTimer()
{
    if (mCurrentState == Idle)
        throw "Cannot reset timer. Timer is idle";

    mTimer->stop();
    mCurrentRemaining = mCurrentTotal;
    switchState(Idle);
    callUpdateTimer();
}

int Pomodoro::getConfig(QString name)
{
    if (name == "workRounds")
        return mWorkRounds;
    else if (name == "timeWork")
        return mTimeWork;
    else if (name == "timeShortBreak")
        return mTimeShortBreak;
    else if (name == "timerLongBreak")
        return mTimeLongBreak;

    qWarning() << name << " configutation not found cannot get";

    return 0;
}

void Pomodoro::setConfig(QString name, int value)
{
    bool shouldUpdateRound = false;

    if (name == "workRounds") {
        mWorkRounds = value;
        shouldUpdateRound = true;
    } else if (name == "timeWork")
        mTimeWork = value;
    else if (name == "timeShortBreak")
        mTimeShortBreak = value;
    else if (name == "timerLongBreak")
        mTimeLongBreak = value;
    else
        qWarning() << name << " configutation not found cannot set";

    updateConfig(shouldUpdateRound);
}

QString Pomodoro::roundToString(Pomodoro::Round round)
{
    if (round == Work)
        return "Work";
    else if (round == ShortBreak)
        return "Short Break";

    return "Long Break";
}

void Pomodoro::switchRound(Pomodoro::Round round)
{
    mCurrentRound = round;

    if (round == Work)
        mCurrentTotal = mTimeWork*60;
    else if (round == ShortBreak)
        mCurrentTotal = mTimeShortBreak*60;
    else if (round == LongBreak)
        mCurrentTotal = mTimeLongBreak*60;

    mCurrentRemaining = mCurrentTotal;

    emit updateRound(mCurrentRound, mRound, mWorkRounds);
    callUpdateTimer();
}

void Pomodoro::switchState(Pomodoro::State state)
{
    mCurrentState = state;
    emit updateState(state);
}

void Pomodoro::callUpdateTimer()
{
    emit updateTimer(mCurrentRemaining, mCurrentTotal);
}

void Pomodoro::reset()
{
    mRound = 1;
}

void Pomodoro::updateConfig(bool shouldUpdateRound)
{
    if (mCurrentState == Idle) {
        switchRound(mCurrentRound);
    }

    if (shouldUpdateRound) {
        emit updateRound(mCurrentRound, mRound, mWorkRounds);
    }
}

void Pomodoro::intervalUpdate()
{
    mCurrentRemaining--;

    if (mCurrentRemaining < 0) {
        if (mCurrentRound == Work && mRound >= mWorkRounds)
            switchRound(LongBreak);
        else if (mCurrentRound == Work)
            switchRound(ShortBreak);
        else if (mCurrentRound == ShortBreak) {
            mRound++;
            switchRound(Work);
        } else {
            reset();
            switchRound(Work);
        }
    } else
        callUpdateTimer();
}
