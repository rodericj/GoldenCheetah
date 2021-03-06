/*
 * Copyright (c) 2010 Mark Liversedge (liversedge@gmail.com)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <math.h>
#include <float.h>
#include "LTMTrend.h"

#include <QDebug>

LTMTrend::LTMTrend(double *xdata, double *ydata, int count) :
          points(0.0), sumX(0.0), sumY(0.0), sumXsquared(0.0),
          sumYsquared(0.0), sumXY(0.0), a(0.0), b(0.0)
{
    if (count == 0) return;

    for (int i = 0; i < count; i++) addXY(xdata[i], ydata[i]);
}

void
LTMTrend::addXY(double& x, double& y)
{
    points++;
    sumX += x;
    sumY += y;
    sumXsquared += x * x;
    sumYsquared += y * y;
    sumXY += x * y;
    calc();
}

void
LTMTrend::calc()
{
    if (points > 2) {
        if (fabs( double(points) * sumXsquared - sumX * sumX) > DBL_EPSILON) {
            b = ( double(points) * sumXY - sumY * sumX) /
                ( double(points) * sumXsquared - sumX * sumX);
            a = (sumY - b * sumX) / double(points);
        }
    }
}
