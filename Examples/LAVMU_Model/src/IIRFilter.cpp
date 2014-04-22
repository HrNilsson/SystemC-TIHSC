/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-7 by Raw Material Software ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   JUCE is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with JUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330,
   Boston, MA 02111-1307 USA

  ------------------------------------------------------------------------------

   If you'd like to release a closed-source product which uses JUCE, commercial
   licenses are also available: visit www.rawmaterialsoftware.com/juce for
   more information.

   Modified by: KBE / 2007.10.10 to be used in example for FPGA implementation

  ==============================================================================
*/
#include <cmath>
#include <cwchar>
#include <typeinfo>
#include <string.h>
#include "IIRFilter.h"
#include "defs.h"

/** Returns the larger of two values. */
inline float  jmax (const float a, const float b) { return (a < b) ? b : a; }

/** Returns the larger of two values. */
inline double jmax (const double a, const double b) { return (a < b) ? b : a; }

//==============================================================================
IIRFilter::IIRFilter()
    : active (false)
{
	reset();
}

IIRFilter::IIRFilter (const IIRFilter& other)
    : active (other.active)
{
    memcpy (coefficients, other.coefficients, sizeof (coefficients));
	reset();
}

IIRFilter::~IIRFilter()
{
}

void IIRFilter::reset()
{
    x1 = 0; x1_fix = 0;
    x2 = 0; x2_fix = 0;
    y1 = 0; y1_fix = 0;
    y2 = 0; y2_fix = 0;
}

void IIRFilter::processSamples (float* const samples,
                                const int numSamples)
{
    if (active)
    {
        for (int i = 0; i < numSamples; ++i)
        {
            const float in = samples[i];

            float out = coefficients[0] * in
                         + coefficients[1] * x1
                         + coefficients[2] * x2
                         - coefficients[4] * y1
                         - coefficients[5] * y2;

            if (! (out < -1.0e-8 || out > 1.0e-8))
                out = 0;

            x2 = x1;
            x1 = in;
            y2 = y1;
            y1 = out;

            samples[i] = out;
        }
    }
}

void IIRFilter::processSamples (int* const samples,
                                const int numSamples)
{
    if (active)
    {
        for (int i = 0; i < numSamples; ++i)
        {
            const int in = samples[i];

            int out = coef_fixed[0] * in
                         + coef_fixed[1] * x1_fix
                         + coef_fixed[2] * x2_fix
                         - coef_fixed[4] * y1_fix
                         - coef_fixed[5] * y2_fix;

			// Scale filter
			out >>= (ALGO_BITS-1);

            x2_fix = x1_fix;
            x1_fix = in;
            y2_fix = y1_fix;
            y1_fix = out;

            samples[i] = out;
        }
    }
}

//==============================================================================
void IIRFilter::makeLowPass (const double sampleRate,
                             const double frequency)
{
    const double n = 1.0 / tan (double_Pi * frequency / sampleRate);
    const double nSquared = n * n;
    const double c1 = 1.0 / (1.0 + sqrt (2.0) * n + nSquared);

    setCoefficients (c1,
                     c1 * 2.0f,
                     c1,
                     1.0,
                     c1 * 2.0 * (1.0 - nSquared),
                     c1 * (1.0 - sqrt (2.0) * n + nSquared));
}

void IIRFilter::makeHighPass (const double sampleRate,
                              const double frequency)
{
    const double n = tan (double_Pi * frequency / sampleRate);
    const double nSquared = n * n;
    const double c1 = 1.0 / (1.0 + sqrt (2.0) * n + nSquared);

    setCoefficients (c1,
                     c1 * -2.0f,
                     c1,
                     1.0,
                     c1 * 2.0 * (nSquared - 1.0),
                     c1 * (1.0 - sqrt (2.0) * n + nSquared));
}

void IIRFilter::makeLowShelf (const double sampleRate,
                              const double cutOffFrequency,
                              const double Q,
                              const float gainFactor)
{
    const double A = jmax (0.0f, gainFactor);
    const double aminus1 = A - 1.0;
    const double aplus1 = A + 1.0;
    const double omega = (double_Pi * 2.0 * jmax (cutOffFrequency, 2.0)) / sampleRate;
    const double coso = cos (omega);
    const double beta = sin (omega) * sqrt (A) / Q;
    const double aminus1TimesCoso = aminus1 * coso;

    setCoefficients (A * (aplus1 - aminus1TimesCoso + beta),
                     A * 2.0 * (aminus1 - aplus1 * coso),
                     A * (aplus1 - aminus1TimesCoso - beta),
                     aplus1 + aminus1TimesCoso + beta,
                     -2.0 * (aminus1 + aplus1 * coso),
                     aplus1 + aminus1TimesCoso - beta);
}

void IIRFilter::makeHighShelf (const double sampleRate,
                               const double cutOffFrequency,
                               const double Q,
                               const float gainFactor)
{
    const double A = jmax (0.0f, gainFactor);
    const double aminus1 = A - 1.0;
    const double aplus1 = A + 1.0;
    const double omega = (double_Pi * 2.0 * jmax (cutOffFrequency, 2.0)) / sampleRate;
    const double coso = cos (omega);
    const double beta = sin (omega) * sqrt (A) / Q;
    const double aminus1TimesCoso = aminus1 * coso;

    setCoefficients (A * (aplus1 + aminus1TimesCoso + beta),
                     A * -2.0 * (aminus1 + aplus1 * coso),
                     A * (aplus1 + aminus1TimesCoso - beta),
                     aplus1 - aminus1TimesCoso + beta,
                     2.0 * (aminus1 - aplus1 * coso),
                     aplus1 - aminus1TimesCoso - beta);
}

void IIRFilter::makeBandPass (const double sampleRate,
                              const double centreFrequency,
                              const double Q,
                              const float gainFactor)
{
    const double A = jmax (0.0f, gainFactor);
    const double omega = (double_Pi * 2.0 * jmax (centreFrequency, 2.0)) / sampleRate;
    const double alpha = 0.5 * sin (omega) / Q;
    const double c2 = -2.0 * cos (omega);
    const double alphaTimesA = alpha * A;
    const double alphaOverA = alpha / A;

    setCoefficients (1.0 + alphaTimesA,
                     c2,
                     1.0 - alphaTimesA,
                     1.0 + alphaOverA,
                     c2,
                     1.0 - alphaOverA);
}

void IIRFilter::makeInactive()
{
    active = false;
}

//==============================================================================
void IIRFilter::copyCoefficientsFrom (const IIRFilter& other)
{
    memcpy (coefficients, other.coefficients, sizeof (coefficients));
    active = other.active;
}

//==============================================================================
void IIRFilter::setCoefficients (double c1,
                                 double c2,
                                 double c3,
                                 double c4,
                                 double c5,
                                 double c6)
{
    const double a = 1.0 / c4;

    c1 *= a;
    c2 *= a;
    c3 *= a;
    c5 *= a;
    c6 *= a;

    coefficients[0] = (float) c1;
    coefficients[1] = (float) c2;
    coefficients[2] = (float) c3;
    coefficients[3] = (float) c4;
    coefficients[4] = (float) c5;
    coefficients[5] = (float) c6;

	for (int i = 0; i < 6; i++)
	{
		coef_fixed[i] = float2fixed(coefficients[i]);
	}

    active = true;
}
