#include "types.h"
#include "JSystem/JUtility/JUTFader.h"
#include "JSystem/JUtility/TColor.h"
#include "JSystem/J2D/J2DGrafContext.h"

JUTFader::JUTFader(int p1, int p2, int p3, int p4, JUtility::TColor color)
    : mColor(color), mViewBox(p1, p2, p1 + p3, p2 + p4)
{
    mStatus = Status_Out;
    mTicksTarget = 0;
    mTicksRun = 0;
    _28 = Status_Out;
    mEStatus = -1;
}

void JUTFader::control()
{
    if (0 <= mEStatus && mEStatus-- == 0)
        mStatus = _28;

    if (mStatus == Status_In)
        return;

    switch (mStatus)
    {
    case Status_Out:
        mColor.a = 0xFF;
        break;
    case Status_FadingIn:
        mColor.a = 0xFF - ((++mTicksRun * 0xFF) / mTicksTarget);
        if (mTicksRun >= mTicksTarget)
        {
            mStatus = Status_In;
        }
        break;
    case Status_FadingOut:
        mColor.a = ((++mTicksRun * 0xFF) / mTicksTarget);
        if (mTicksRun >= mTicksTarget)
        {
            mStatus = Status_Out;
        }
        break;
    }
    draw();
}

void JUTFader::draw()
{
    if (mColor.a == 0)
        return;

    J2DOrthoGraph orthograph;
    orthograph.setColor(mColor);
    orthograph.fillBox(mViewBox);
}

void JUTFader::start(int)
{
    // UNUSED FUNCTION
}

bool JUTFader::startFadeIn(int duration)
{    
    bool fadingOut = mStatus == Status_Out;

    if (fadingOut) {
        mStatus = Status_FadingIn;
        mTicksRun = 0;
        mTicksTarget = duration;
    }

    return fadingOut;
}

bool JUTFader::startFadeOut(int duration)
{
    bool fadingIn = mStatus == Status_In;

    if (fadingIn) {
        mStatus = Status_FadingOut;
        mTicksRun = 0;
        mTicksTarget = duration;
    }

    return fadingIn;
}

void JUTFader::setStatus(JUTFader::EStatus i_status, int param_1)
{
    switch (i_status)
    {
    case Status_Out:
        if (param_1 != 0)
        {
            _28 = Status_Out;
            mEStatus = (u16)param_1;
            break;
        }

        mStatus = Status_Out;
        _28 = Status_Out;
        mEStatus = 0;
        break;
    case Status_In:
        if (param_1 != 0)
        {
            _28 = Status_In;
            mEStatus = (u16)param_1;
            break;
        }

        mStatus = Status_In;
        _28 = Status_In;
        mEStatus = 0;
        break;
    }
}