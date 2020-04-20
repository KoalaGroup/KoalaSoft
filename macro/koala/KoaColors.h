/*
 * Copyright (c) 2019 Luigi Pertoldi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Author: Luigi Pertoldi - pertoldi@pd.infn.it
 * Created: 26 Sep 2019
 *
 * Adapted: Yong Zhou <y.zhou@fz-juelich.de>
 * Downloaded: 16 Dec 2018
 *
 * Implementation of Paul Tol's color palettes, as presented in
 *
 *   https://personal.sron.nl/~pault/data/colourschemes.pdf
 *
 * for the ROOT CERN software suite. Example usage:
 * ```
 * #include KoaColors.h
 * using namespace KoaColors;
 * void routine() {
 *   init_KoaColors();
 *   hist->SetLineColor(kTVibBlue);
 * }
 * ```
 * Please read the technical note for a detailed explanation of the color palettes.
 */

#ifndef KOACOLORS_H
#define KOACOLORS_H

#include "TColor.h"
#include "TStyle.h"

namespace KoaColors {
    /*
     * Handy enum for later color referencing
     */
    enum {
        // Bright color scheme
        kTBriBlue        = 9000,
        kTBriCyan        = 9001,
        kTBriGreen       = 9002,
        kTBriYellow      = 9003,
        kTBriRed         = 9004,
        kTBriPurple      = 9005,
        kTBriGrey        = 9006,

        // Vibrant color scheme
        kTVibBlue        = 9007,
        kTVibCyan        = 9008,
        kTVibTeal        = 9009,
        kTVibOrange      = 9010,
        kTVibRed         = 9011,
        kTVibMagenta     = 9012,
        kTVibGrey        = 9013,

        // Muted color scheme
        kTMutIndigo      = 9014,
        kTMutCyan        = 9015,
        kTMutTeal        = 9016,
        kTMutGreen       = 9017,
        kTMutOlive       = 9018,
        kTMutSand        = 9019,
        kTMutRose        = 9020,
        kTMutWine        = 9021,
        kTMutPurple      = 9022,
        kTMutPaleGrey    = 9023,

        // Light color scheme
        kTLigLightBlue   = 9024,
        kTLigLightCyan   = 9025,
        kTLigMint        = 9026,
        kTLigPear        = 9027,
        kTLigOlive       = 9028,
        kTLigLightYellow = 9029,
        kTLigOrange      = 9030,
        kTLigPink        = 9031,
        kTLigPaleGrey    = 9032,

        // To label "bad" data (see BuRd and PRGn palettes below)
        kTBadData        = 9033
    };

    /* init_KoaColors()
     *
     * Define colors. Please call this function before doing anything
     */
    void init_KoaColors() {
        gStyle->SetColorModelPS(0);

        // Bright color scheme
        new TColor(kTBriBlue,         68./255, 119./255, 170./255, "tol-bri-blue"       );
        new TColor(kTBriCyan,        102./255, 204./255, 238./255, "tol-bri-cyan"       );
        new TColor(kTBriGreen,        34./255, 136./255,  51./255, "tol-bri-green"      );
        new TColor(kTBriYellow,      204./255, 187./255,  68./255, "tol-bri-yellow"     );
        new TColor(kTBriRed,         238./255, 102./255, 119./255, "tol-bri-red"        );
        new TColor(kTBriPurple,      170./255,  51./255, 119./255, "tol-bri-purple"     );
        new TColor(kTBriGrey,        187./255, 187./255, 187./255, "tol-bri-grey"       );

        // Vibrant color scheme
        new TColor(kTVibBlue,          0./255, 119./255, 187./255, "tol-vib-blue"       );
        new TColor(kTVibCyan,         51./255, 187./255, 238./255, "tol-vib-cyan"       );
        new TColor(kTVibTeal,          0./255, 153./255, 136./255, "tol-vib-teal"       );
        new TColor(kTVibOrange,      238./255, 119./255,  51./255, "tol-vib-orange"     );
        new TColor(kTVibRed,         204./255,  51./255,  17./255, "tol-vib-red"        );
        new TColor(kTVibMagenta,     238./255,  51./255, 119./255, "tol-vib-magenta"    );
        new TColor(kTVibGrey,        187./255, 187./255, 187./255, "tol-vib-grey"       );

        // Muted color scheme
        new TColor(kTMutIndigo,       51./255,  34./255, 136./255, "tol-mut-indigo"     );
        new TColor(kTMutCyan,        136./255, 204./255, 238./255, "tol-mut-cyan"       );
        new TColor(kTMutTeal,         68./255, 170./255, 153./255, "tol-mut-teal"       );
        new TColor(kTMutGreen,        17./255, 119./255,  51./255, "tol-mut-green"      );
        new TColor(kTMutOlive,       153./255, 153./255,  51./255, "tol-mut-olive"      );
        new TColor(kTMutSand,        221./255, 204./255, 119./255, "tol-mut-sand"       );
        new TColor(kTMutRose,        204./255, 102./255, 119./255, "tol-mut-rose"       );
        new TColor(kTMutWine,        136./255,  34./255,  85./255, "tol-mut-wine"       );
        new TColor(kTMutPurple,      170./255,  68./255, 153./255, "tol-mut-purple"     );
        new TColor(kTMutPaleGrey,    221./255, 221./255, 221./255, "tol-mut-palegrey"   );

        // Light color scheme
        new TColor(kTLigLightBlue,   119./255, 170./255, 221./255, "tol-lig-lightblue"  );
        new TColor(kTLigLightCyan,   153./255, 221./255, 255./255, "tol-lig-lightcyan"  );
        new TColor(kTLigMint,         68./255, 187./255, 153./255, "tol-lig-mint"       );
        new TColor(kTLigPear,        187./255, 204./255,  51./255, "tol-lig-pear"       );
        new TColor(kTLigOlive,       170./255, 170./255,   0./255, "tol-lig-olive"      );
        new TColor(kTLigLightYellow, 238./255, 221./255, 136./255, "tol-lig-lightyellow");
        new TColor(kTLigOrange,      238./255, 136./255, 102./255, "tol-lig-orange"     );
        new TColor(kTLigPink,        255./255, 170./255, 187./255, "tol-lig-pink"       );
        new TColor(kTLigPaleGrey,    221./255, 221./255, 221./255, "tol-lig-palegrey"   );

        new TColor(kTBadData,        255./255, 238./255, 153./255, "tol-bad-data"       );
    }

    /* set_KoaPalette_Sunset
     *
     * Set sunset diverging colour scheme as the default palette
     * `ncols` specifies how many colors the palette should contain
     *
     * Use `kWhite` to label "bad" data
     */
    void set_KoaPalette_Sunset(int ncols = 50) {
        double R[11] = { 54./255,  74./255, 110./255, 152./255, 194./255, 234./255, 254./255, 253./255, 246./255, 221./255, 165./255};
        double G[11] = { 75./255, 123./255, 166./255, 202./255, 228./255, 236./255, 218./255, 179./255, 126./255,  61./255,   0./255};
        double B[11] = {154./255, 183./255, 205./255, 225./255, 239./255, 204./255, 139./255, 102./255,  75./255,  45./255,  38./255};
        double l[11] = {     0.0,      0.1,      0.2,      0.3,      0.4,      0.5,      0.6,      0.7,      0.8,      0.9,      1.0};
        TColor::CreateGradientColorTable(11, l, R, G, B, ncols);
    }

    /* set_KoaPalette_BuRd
     *
     * Set BuRd diverging colour scheme as the default palette
     * `ncols` specifies how many colors the palette should contain
     *
     * Use `kTBadData` to label "bad" data
     */
    void set_KoaPalette_BuRd(int ncols = 50) {
        double R[9] = { 33./255,  67./255, 146./255, 209./255, 247./255, 253./255, 244./255, 214./255, 178./255};
        double G[9] = {102./255, 147./255, 197./255, 229./255, 247./255, 219./255, 165./255,  96./255,  24./255};
        double B[9] = {172./255, 195./255, 222./255, 240./255, 247./255, 199./255, 130./255,  77./255,  43./255};
        double l[9] = {   0.000,    0.125,    0.250,    0.375,    0.500,    0.625,    0.750,    0.875,    1.000};
        TColor::CreateGradientColorTable(11, l, R, G, B, ncols);
    }

    /* set_KoaPalette_PRGn
     *
     * Set PRGn diverging colour scheme as the default palette
     * `ncols` specifies how many colors the palette should contain
     *
     * Use `kTBadData` to label "bad" data
     */
    void set_KoaPalette_PRGn(int ncols = 50) {
        double R[9] = {118./255, 153./255, 194./255, 231./255, 247./255, 217./255, 172./255,  90./255,  27./255};
        double G[9] = { 42./255, 112./255, 165./255, 212./255, 247./255, 240./255, 211./255, 174./255, 120./255};
        double B[9] = {131./255, 171./255, 207./255, 232./255, 247./255, 211./255, 158./255,  97./255,  55./255};
        double l[9] = {   0.000,    0.125,    0.250,    0.375,    0.500,    0.625,    0.750,    0.875,    1.000};
        TColor::CreateGradientColorTable(11, l, R, G, B, ncols);
    }
};

#endif
