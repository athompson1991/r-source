/* ppr.f -- translated by f2c (version 19971204).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

struct bdrparms_1_ {
    integer ifl, lf;
    doublereal span, alpha, big;
};

#define bdrparms_1 (*(struct bdrparms_1_ *) &bdrparms_)

struct bdrz01_1_ {
    doublereal conv;
    integer maxit, mitone;
    doublereal cutmin, fdel, cjeps;
    integer mitcj;
};

#define bdrz01_1 (*(struct bdrz01_1_ *) &bdrz01_)

struct bdrspsmooth_1_ {
    doublereal df, gcvpen;
    integer ismethod;
};

#define bdrspsmooth_1 (*(struct bdrspsmooth_1_ *) &bdrspsmooth_)

struct bdrspans_1_ {
    doublereal spans[3];
};

#define bdrspans_1 (*(struct bdrspans_1_ *) &bdrspans_)

struct bdrconsts_1_ {
    doublereal big, sml, eps;
};

#define bdrconsts_1 (*(struct bdrconsts_1_ *) &bdrconsts_)

/* Initialized data */

struct {
    doublereal e_1[2];
    integer e_2;
    } bdrspsmooth_ = { 4., 1., 0 };

struct {
    integer e_1[2];
    doublereal e_2[3];
    } bdrparms_ = { 6, 2, 0., 0., 1e20 };

struct {
    doublereal e_1[3];
    } bdrspans_ = { .05, .2, .5 };

struct {
    doublereal e_1[3];
    } bdrconsts_ = { 1e20, 1e-7, .001 };

struct {
    doublereal e_1;
    integer e_2[2];
    doublereal e_3[3];
    integer e_4;
    } bdrz01_ = { .005, 20, 20, .1, .02, .001, 1 };


/* Table of constant values */

static integer c__1 = 1;
static integer c__0 = 0;
static real c_b213 = 0.f;
static integer c__4 = 4;
static integer c__8 = 8;
static integer c__6 = 6;
static integer c__2 = 2;


/*     Modified from the SMART package by J.H. Friedman, 10/10/84 */
/*     Main change is to add spline smoothing modified from BRUTO, */
/*     calling code written for smooth.spline in S. */

/*     B.D. Ripley (ripley@stats.ox.ac.uk)  1994-7. */


/* Subroutine */ int bdrsmart(integer *m, integer *mu, integer *p, integer *
	q, integer *n, doublereal *w, doublereal *x, doublereal *y, 
	doublereal *ww, doublereal *smod, integer *nsmod, doublereal *sp, 
	integer *nsp, doublereal *dp, integer *ndp, doublereal *edf)
{
    /* System generated locals */
    integer x_dim1, x_offset, y_dim1, y_offset;

    /* Local variables */
    extern /* Subroutine */ int bdrsmart1(integer *, integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);

    /* Parameter adjustments */
    --edf;
    --ww;
    y_dim1 = *q;
    y_offset = y_dim1 + 1;
    y -= y_offset;
    x_dim1 = *p;
    x_offset = x_dim1 + 1;
    x -= x_offset;
    --w;
    --smod;
    --sp;
    --dp;

    /* Function Body */
    smod[1] = (doublereal) (*m);
    smod[2] = (doublereal) (*p);
    smod[3] = (doublereal) (*q);
    smod[4] = (doublereal) (*n);
    bdrsmart1(m, mu, p, q, n, &w[1], &x[x_offset], &y[y_offset], &ww[1], &
	    smod[6], &smod[*q + 6], &smod[*q + 7], &smod[*q + 7 + *p * *m], &
	    smod[*q + 7 + *m * (*p + *q)], &smod[*q + 7 + *m * (*p + *q + *n)]
	    , &smod[*q + 7 + *m * (*p + *q + (*n << 1))], &sp[1], &sp[*q * *n 
	    + 1], &sp[*n * (*q + 15) + 1], &sp[*n * (*q + 15) + *q + 1], &dp[
	    1], &smod[5], &edf[1]);
    return 0;
} /* bdrsmart_ */

/* Subroutine */ int bdrsmart1(integer *m, integer *mu, integer *p, integer *
	q, integer *n, doublereal *w, doublereal *x, doublereal *y, 
	doublereal *ww, doublereal *yb, doublereal *ys, doublereal *a, 
	doublereal *b, doublereal *f, doublereal *t, doublereal *asr, 
	doublereal *r__, doublereal *sc, doublereal *bt, doublereal *g, 
	doublereal *dp, doublereal *flm, doublereal *edf)
{
    /* System generated locals */
    integer x_dim1, x_offset, a_dim1, a_offset, b_dim1, b_offset, f_dim1, 
	    f_offset, t_dim1, t_offset, r_dim1, r_offset, sc_dim1, sc_offset, 
	    g_dim1, g_offset, i__1, i__2, i__3;
    doublereal d__1;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static integer i__, j, l;
    static doublereal s;
    extern /* Subroutine */ int bdrfulfit(integer *, integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *), 
	    bdrsubfit(integer *, integer *, integer *, integer *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static integer lm;
    static doublereal sw;
    extern /* Subroutine */ int bdrsort(doublereal *, doublereal *, integer *
	    , integer *);

/* 			 ^^^ really (ndb) of  BDRsmart(.) */
    /* Parameter adjustments */
    --edf;
    g_dim1 = *p;
    g_offset = g_dim1 + 1;
    g -= g_offset;
    a_dim1 = *p;
    a_offset = a_dim1 + 1;
    a -= a_offset;
    --bt;
    b_dim1 = *q;
    b_offset = b_dim1 + 1;
    b -= b_offset;
    --yb;
    --ww;
    sc_dim1 = *n;
    sc_offset = sc_dim1 + 1;
    sc -= sc_offset;
    r_dim1 = *q;
    r_offset = r_dim1 + 1;
    r__ -= r_offset;
    t_dim1 = *n;
    t_offset = t_dim1 + 1;
    t -= t_offset;
    f_dim1 = *n;
    f_offset = f_dim1 + 1;
    f -= f_offset;
    x_dim1 = *p;
    x_offset = x_dim1 + 1;
    x -= x_offset;
    --w;
    --y;
    --dp;

    /* Function Body */
    sw = 0.;
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
/* L161: */
	sw += w[j];
    }
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *q;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    r__[i__ + j * r_dim1] = y[*q * (j - 1) + i__];
/* L201: */
	}
    }
    i__2 = *q;
    for (i__ = 1; i__ <= i__2; ++i__) {
	s = 0.;
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    s += w[j] * r__[i__ + j * r_dim1];
/* L251: */
	}
	yb[i__] = s / sw;
/* L241: */
    }
/*     yb is vector of means */
    i__2 = *n;
    for (j = 1; j <= i__2; ++j) {
	i__1 = *q;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* L261: */
	    r__[i__ + j * r_dim1] -= yb[i__];
	}
    }
    *ys = 0.f;
    i__1 = *q;
    for (i__ = 1; i__ <= i__1; ++i__) {
	s = 0.f;
	i__2 = *n;
	for (j = 1; j <= i__2; ++j) {
/* L291: */
/* Computing 2nd power */
	    d__1 = r__[i__ + j * r_dim1];
	    s += w[j] * (d__1 * d__1);
	}
	*ys += ww[i__] * s / sw;
/* L281: */
    }
    if (*ys > 0.) {
	goto L311;
    }
/*     ys is the overall standard deviation -- quit if zero */
    return 0;
L311:
    *ys = sqrt(*ys);
    s = 1.f / *ys;
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *q;
	for (i__ = 1; i__ <= i__2; ++i__) {
/* L331: */
	    r__[i__ + j * r_dim1] *= s;
	}
    }
/*     r is now standardized residuals */
/*     subfit adds up to m  terms one at time; lm is the number fitted. */
    bdrsubfit(m, p, q, n, &w[1], &sw, &x[x_offset], &r__[r_offset], &ww[1], &
	    lm, &a[a_offset], &b[b_offset], &f[f_offset], &t[t_offset], asr, &
	    sc[sc_offset], &bt[1], &g[g_offset], &dp[1], &edf[1]);
    if (bdrparms_1.lf <= 0) {
	goto L9999;
    }
    bdrfulfit(&lm, &bdrparms_1.lf, p, q, n, &w[1], &sw, &x[x_offset], &r__[
	    r_offset], &ww[1], &a[a_offset], &b[b_offset], &f[f_offset], &t[
	    t_offset], asr, &sc[sc_offset], &bt[1], &g[g_offset], &dp[1], &
	    edf[1]);
/* REPEAT */
L371:
    i__2 = lm;
    for (l = 1; l <= i__2; ++l) {
	sc[l + sc_dim1] = l + .1f;
	s = 0.;
	i__1 = *q;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* L391: */
	    s += ww[i__] * (d__1 = b[i__ + l * b_dim1], abs(d__1));
	}
	sc[l + (sc_dim1 << 1)] = -s;
/* L381: */
    }
    bdrsort(&sc[(sc_dim1 << 1) + 1], &sc[sc_offset], &c__1, &lm);
    i__2 = *n;
    for (j = 1; j <= i__2; ++j) {
	i__1 = *q;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* L461: */
	    r__[i__ + j * r_dim1] = y[*q * (j - 1) + i__];
	}
    }
    i__1 = *q;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = *n;
	for (j = 1; j <= i__2; ++j) {
	    r__[i__ + j * r_dim1] -= yb[i__];
	    s = 0.f;
	    i__3 = lm;
	    for (l = 1; l <= i__3; ++l) {
/* L541: */
		s += b[i__ + l * b_dim1] * f[j + l * f_dim1];
	    }
	    r__[i__ + j * r_dim1] = r__[i__ + j * r_dim1] / *ys - s;
/* L531: */
	}
/* L521: */
    }
    if (lm <= *mu) {
	goto L9999;
    }
    l = (integer) sc[lm + sc_dim1];
/* back to integer */
    *asr = 0.;
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *q;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    r__[i__ + j * r_dim1] += b[i__ + l * b_dim1] * f[j + l * f_dim1];
/* L561: */
/* Computing 2nd power */
	    d__1 = r__[i__ + j * r_dim1];
	    *asr += w[j] * ww[i__] * (d__1 * d__1);
	}
    }
    *asr /= sw;
    if (l >= lm) {
	goto L591;
    }
    i__2 = *p;
    for (i__ = 1; i__ <= i__2; ++i__) {
/* L601: */
	a[i__ + l * a_dim1] = a[i__ + lm * a_dim1];
    }
    i__2 = *q;
    for (i__ = 1; i__ <= i__2; ++i__) {
/* L611: */
	b[i__ + l * b_dim1] = b[i__ + lm * b_dim1];
    }
    i__2 = *n;
    for (j = 1; j <= i__2; ++j) {
	f[j + l * f_dim1] = f[j + lm * f_dim1];
/* L621: */
	t[j + l * t_dim1] = t[j + lm * t_dim1];
    }
L591:
    --lm;
    bdrfulfit(&lm, &bdrparms_1.lf, p, q, n, &w[1], &sw, &x[x_offset], &r__[
	    r_offset], &ww[1], &a[a_offset], &b[b_offset], &f[f_offset], &t[
	    t_offset], asr, &sc[sc_offset], &bt[1], &g[g_offset], &dp[1], &
	    edf[1]);
    goto L371;
/* END REPEAT */
L9999:
    *flm = (doublereal) lm;
    return 0;
} /* bdrsmart1_ */

/* Subroutine */ int bdrsubfit(integer *m, integer *p, integer *q, integer *
	n, doublereal *w, doublereal *sw, doublereal *x, doublereal *r__, 
	doublereal *ww, integer *lm, doublereal *a, doublereal *b, doublereal 
	*f, doublereal *t, doublereal *asr, doublereal *sc, doublereal *bt, 
	doublereal *g, doublereal *dp, doublereal *edf)
{
    /* System generated locals */
    integer x_dim1, x_offset, a_dim1, a_offset, f_dim1, f_offset, t_dim1, 
	    t_offset, r_dim1, r_offset, sc_dim1, sc_offset, g_dim1, g_offset, 
	    b_dim1, b_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, l, iflsv;
    extern /* Subroutine */ int bdrfulfit(integer *, integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *), 
	    bdronetrm(integer *, integer *, integer *, integer *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal asrold;
    extern /* Subroutine */ int bdrnewb(integer *, integer *, doublereal *, 
	    doublereal *);

    /* Parameter adjustments */
    --edf;
    g_dim1 = *p;
    g_offset = g_dim1 + 1;
    g -= g_offset;
    a_dim1 = *p;
    a_offset = a_dim1 + 1;
    a -= a_offset;
    --bt;
    b_dim1 = *q;
    b_offset = b_dim1 + 1;
    b -= b_offset;
    --ww;
    sc_dim1 = *n;
    sc_offset = sc_dim1 + 1;
    sc -= sc_offset;
    t_dim1 = *n;
    t_offset = t_dim1 + 1;
    t -= t_offset;
    f_dim1 = *n;
    f_offset = f_dim1 + 1;
    f -= f_offset;
    r_dim1 = *q;
    r_offset = r_dim1 + 1;
    r__ -= r_offset;
    x_dim1 = *p;
    x_offset = x_dim1 + 1;
    x -= x_offset;
    --w;
    --dp;

    /* Function Body */
    *asr = bdrparms_1.big;
    *lm = 0;
    i__1 = *m;
    for (l = 1; l <= i__1; ++l) {
	++(*lm);
	asrold = *asr;
	bdrnewb(lm, q, &ww[1], &b[b_offset]);
	bdronetrm(&c__0, p, q, n, &w[1], sw, &x[x_offset], &r__[r_offset], &
		ww[1], &a[*lm * a_dim1 + 1], &b[*lm * b_dim1 + 1], &f[*lm * 
		f_dim1 + 1], &t[*lm * t_dim1 + 1], asr, &sc[sc_offset], &g[
		g_offset], &dp[1], &edf[1]);
	i__2 = *n;
	for (j = 1; j <= i__2; ++j) {
	    i__3 = *q;
	    for (i__ = 1; i__ <= i__3; ++i__) {
/* L10651: */
		r__[i__ + j * r_dim1] -= b[i__ + *lm * b_dim1] * f[j + *lm * 
			f_dim1];
	    }
	}
	if (*lm == 1) {
	    goto L10641;
	}
	if (bdrparms_1.lf <= 0) {
	    goto L10690;
	}
	if (*lm == *m) {
	    return 0;
	}
	iflsv = bdrparms_1.ifl;
	bdrparms_1.ifl = 0;
	bdrfulfit(lm, &c__1, p, q, n, &w[1], sw, &x[x_offset], &r__[r_offset]
		, &ww[1], &a[a_offset], &b[b_offset], &f[f_offset], &t[
		t_offset], asr, &sc[sc_offset], &bt[1], &g[g_offset], &dp[1], 
		&edf[1]);
	bdrparms_1.ifl = iflsv;
L10690:
	if (*asr <= 0. || (asrold - *asr) / asrold < bdrz01_1.conv) {
	    return 0;
	}
L10641:
	;
    }
    return 0;
} /* bdrsubfit_ */

/* Subroutine */ int bdrfulfit(integer *lm, integer *lbf, integer *p, 
	integer *q, integer *n, doublereal *w, doublereal *sw, doublereal *x, 
	doublereal *r__, doublereal *ww, doublereal *a, doublereal *b, 
	doublereal *f, doublereal *t, doublereal *asr, doublereal *sc, 
	doublereal *bt, doublereal *g, doublereal *dp, doublereal *edf)
{
    /* System generated locals */
    integer x_dim1, x_offset, a_dim1, a_offset, f_dim1, f_offset, t_dim1, 
	    t_offset, r_dim1, r_offset, sc_dim1, sc_offset, g_dim1, g_offset, 
	    b_dim1, b_offset, i__1, i__2, i__3;

    /* Local variables */
    static doublereal asri;
    static integer iter, i__, j;
    extern /* Subroutine */ int bdronetrm(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static integer lp;
    static doublereal asrold, fsv;
    static integer isv;

    /* Parameter adjustments */
    --edf;
    --asr;
    g_dim1 = *p;
    g_offset = g_dim1 + 1;
    g -= g_offset;
    a_dim1 = *p;
    a_offset = a_dim1 + 1;
    a -= a_offset;
    --bt;
    b_dim1 = *q;
    b_offset = b_dim1 + 1;
    b -= b_offset;
    --ww;
    sc_dim1 = *n;
    sc_offset = sc_dim1 + 1;
    sc -= sc_offset;
    t_dim1 = *n;
    t_offset = t_dim1 + 1;
    t -= t_offset;
    f_dim1 = *n;
    f_offset = f_dim1 + 1;
    f -= f_offset;
    r_dim1 = *q;
    r_offset = r_dim1 + 1;
    r__ -= r_offset;
    x_dim1 = *p;
    x_offset = x_dim1 + 1;
    x -= x_offset;
    --w;
    --dp;

    /* Function Body */
    if (*lbf <= 0) {
	return 0;
    }
    asri = asr[1];
    iter = 0;
    fsv = bdrz01_1.cutmin;
    isv = bdrz01_1.mitone;
    if (*lbf >= 3) {
	goto L10711;
    }
    bdrz01_1.cutmin = 1.;
    bdrz01_1.mitone = *lbf - 1;
L10711:
    asrold = asri;
    ++iter;
    i__1 = *lm;
    for (lp = 1; lp <= i__1; ++lp) {
	i__2 = *q;
	for (i__ = 1; i__ <= i__2; ++i__) {
/* L10741: */
	    bt[i__] = b[i__ + lp * b_dim1];
	}
	i__2 = *p;
	for (i__ = 1; i__ <= i__2; ++i__) {
/* L10751: */
	    g[i__ + g_dim1 * 3] = a[i__ + lp * a_dim1];
	}
	i__2 = *n;
	for (j = 1; j <= i__2; ++j) {
	    i__3 = *q;
	    for (i__ = 1; i__ <= i__3; ++i__) {
/* L10761: */
		r__[i__ + j * r_dim1] += bt[i__] * f[j + lp * f_dim1];
	    }
	}
	bdronetrm(&c__1, p, q, n, &w[1], sw, &x[x_offset], &r__[r_offset], &
		ww[1], &g[g_dim1 * 3 + 1], &bt[1], &sc[sc_dim1 * 14 + 1], &sc[
		sc_dim1 * 15 + 1], &asri, &sc[sc_offset], &g[g_offset], &dp[1]
		, &edf[lp]);
	if (asri < asrold) {
	    i__3 = *q;
	    for (i__ = 1; i__ <= i__3; ++i__) {
/* L10801: */
		b[i__ + lp * b_dim1] = bt[i__];
	    }
	    i__3 = *p;
	    for (i__ = 1; i__ <= i__3; ++i__) {
/* L10811: */
		a[i__ + lp * a_dim1] = g[i__ + g_dim1 * 3];
	    }
	    i__3 = *n;
	    for (j = 1; j <= i__3; ++j) {
		f[j + lp * f_dim1] = sc[j + sc_dim1 * 14];
/* L10821: */
		t[j + lp * t_dim1] = sc[j + sc_dim1 * 15];
	    }
	} else {
	    asri = asrold;
	}
	i__3 = *n;
	for (j = 1; j <= i__3; ++j) {
	    i__2 = *q;
	    for (i__ = 1; i__ <= i__2; ++i__) {
/* L10841: */
		r__[i__ + j * r_dim1] -= b[i__ + lp * b_dim1] * f[j + lp * 
			f_dim1];
	    }
	}
/* L10731: */
    }
    if (iter <= bdrz01_1.maxit && (asri > 0. && (asrold - asri) / asrold >= 
	    bdrz01_1.conv)) {
	goto L10711;
    }
    bdrz01_1.cutmin = fsv;
    bdrz01_1.mitone = isv;
    if (bdrparms_1.ifl <= 0) {
	goto L10871;
    }
    asr[*lm + 1] = asri;
    asr[1] = asri;
L10871:
    return 0;
} /* bdrfulfit_ */

/* Subroutine */ int bdronetrm(integer *jfl, integer *p, integer *q, integer 
	*n, doublereal *w, doublereal *sw, doublereal *x, doublereal *y, 
	doublereal *ww, doublereal *a, doublereal *b, doublereal *f, 
	doublereal *t, doublereal *asr, doublereal *sc, doublereal *g, 
	doublereal *dp, doublereal *edf)
{
    /* System generated locals */
    integer x_dim1, x_offset, y_dim1, y_offset, sc_dim1, sc_offset, g_dim1, 
	    g_offset, i__1, i__2, i__3;
    doublereal d__1;

    /* Local variables */
    static integer iter, i__, j;
    static doublereal s;
    extern /* Subroutine */ int bdroneone(integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal asrold;

    /* Parameter adjustments */
    g_dim1 = *p;
    g_offset = g_dim1 + 1;
    g -= g_offset;
    --a;
    --b;
    --ww;
    sc_dim1 = *n;
    sc_offset = sc_dim1 + 1;
    sc -= sc_offset;
    --t;
    --f;
    y_dim1 = *q;
    y_offset = y_dim1 + 1;
    y -= y_offset;
    x_dim1 = *p;
    x_offset = x_dim1 + 1;
    x -= x_offset;
    --w;
    --dp;

    /* Function Body */
    iter = 0;
    *asr = bdrparms_1.big;
/* REPEAT */
L10901:
    ++iter;
    asrold = *asr;
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	s = 0.;
	i__2 = *q;
	for (i__ = 1; i__ <= i__2; ++i__) {
/* L10921: */
	    s += ww[i__] * b[i__] * y[i__ + j * y_dim1];
	}
/* L10911: */
	sc[j + sc_dim1 * 13] = s;
    }
/* Computing MAX */
    i__2 = *jfl, i__3 = iter - 1;
    i__1 = max(i__2,i__3);
    bdroneone(&i__1, p, n, &w[1], sw, &sc[sc_dim1 * 13 + 1], &x[x_offset], &
	    a[1], &f[1], &t[1], asr, &sc[sc_offset], &g[g_offset], &dp[1], 
	    edf);
    i__1 = *q;
    for (i__ = 1; i__ <= i__1; ++i__) {
	s = 0.;
	i__2 = *n;
	for (j = 1; j <= i__2; ++j) {
/* L10941: */
	    s += w[j] * y[i__ + j * y_dim1] * f[j];
	}
/* L10931: */
	b[i__] = s / *sw;
    }
    *asr = 0.;
    i__1 = *q;
    for (i__ = 1; i__ <= i__1; ++i__) {
	s = 0.;
	i__2 = *n;
	for (j = 1; j <= i__2; ++j) {
/* L10961: */
/* Computing 2nd power */
	    d__1 = y[i__ + j * y_dim1] - b[i__] * f[j];
	    s += w[j] * (d__1 * d__1);
	}
/* L10951: */
	*asr += ww[i__] * s / *sw;
    }
    if (*q != 1 && (iter <= bdrz01_1.maxit && (*asr > 0. && (asrold - *asr) / 
	    asrold >= bdrz01_1.conv))) {
	goto L10901;
    }
    return 0;
} /* bdronetrm_ */

/* Subroutine */ int bdroneone(integer *ist, integer *p, integer *n, 
	doublereal *w, doublereal *sw, doublereal *y, doublereal *x, 
	doublereal *a, doublereal *f, doublereal *t, doublereal *asr, 
	doublereal *sc, doublereal *g, doublereal *dp, doublereal *edf)
{
    /* System generated locals */
    integer x_dim1, x_offset, sc_dim1, sc_offset, g_dim1, g_offset, i__1, 
	    i__2;
    doublereal d__1;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static integer iter, i__, j, k;
    static doublereal s, v;
    extern /* Subroutine */ int bdrsupsmu(integer *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *), bdrder(integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *), bdrdir(integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static doublereal asrold, sml, cut;
    extern /* Subroutine */ int bdrsort(doublereal *, doublereal *, integer *
	    , integer *);

    /* Parameter adjustments */
    g_dim1 = *p;
    g_offset = g_dim1 + 1;
    g -= g_offset;
    --a;
    sc_dim1 = *n;
    sc_offset = sc_dim1 + 1;
    sc -= sc_offset;
    --t;
    --f;
    x_dim1 = *p;
    x_offset = x_dim1 + 1;
    x -= x_offset;
    --y;
    --w;
    --dp;

    /* Function Body */
    sml = 1. / bdrparms_1.big;
    if (*ist <= 0) {
	if (*p <= 1) {
	    a[1] = 1.;
	}
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    sc[j + (sc_dim1 << 1)] = 1.;
/* L10: */
	}
	bdrdir(p, n, &w[1], sw, &y[1], &x[x_offset], &sc[(sc_dim1 << 1) + 1],
		 &a[1], &dp[1]);
    }
    s = 0.;
    i__1 = *p;
    for (i__ = 1; i__ <= i__1; ++i__) {
	g[i__ + g_dim1] = 0.;
/* Computing 2nd power */
	d__1 = a[i__];
	s += d__1 * d__1;
/* L20: */
    }
    s = 1. / sqrt(s);
    i__1 = *p;
    for (i__ = 1; i__ <= i__1; ++i__) {
	a[i__] *= s;
/* L30: */
    }
    iter = 0;
    *asr = bdrparms_1.big;
    cut = 1.;
/* REPEAT ----------------------------- */
L100:
    ++iter;
    asrold = *asr;
/* REPEAT [inner loop] ----- */
L60:
    s = 0.;
    i__1 = *p;
    for (i__ = 1; i__ <= i__1; ++i__) {
	g[i__ + (g_dim1 << 1)] = a[i__] + g[i__ + g_dim1];
/* Computing 2nd power */
	d__1 = g[i__ + (g_dim1 << 1)];
	s += d__1 * d__1;
/* L70: */
    }
    s = 1.f / sqrt(s);
    i__1 = *p;
    for (i__ = 1; i__ <= i__1; ++i__) {
	g[i__ + (g_dim1 << 1)] *= s;
/* L80: */
    }
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	sc[j + sc_dim1] = j + .1f;
	s = 0.f;
	i__2 = *p;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    s += g[i__ + (g_dim1 << 1)] * x[i__ + j * x_dim1];
/* L91: */
	}
	sc[j + sc_dim1 * 11] = s;
/* L90: */
    }
    bdrsort(&sc[sc_dim1 * 11 + 1], &sc[sc_offset], &c__1, n);
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	k = (integer) sc[j + sc_dim1];
	sc[j + (sc_dim1 << 1)] = y[k];
/* Computing MAX */
	d__1 = w[k];
	sc[j + sc_dim1 * 3] = max(d__1,sml);
/* L110: */
    }
    bdrsupsmu(n, &sc[sc_dim1 * 11 + 1], &sc[(sc_dim1 << 1) + 1], &sc[sc_dim1 
	    * 3 + 1], &c__1, &bdrparms_1.span, &bdrparms_1.alpha, &sc[sc_dim1 
	    * 12 + 1], &sc[(sc_dim1 << 2) + 1], edf);
    s = 0.;
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
/* Computing 2nd power */
	d__1 = sc[j + (sc_dim1 << 1)] - sc[j + sc_dim1 * 12];
	s += sc[j + sc_dim1 * 3] * (d__1 * d__1);
/* L120: */
    }
    s /= *sw;
    if (s < *asr) {
	goto L140;
    }
    cut *= .5f;
    if (cut < bdrz01_1.cutmin) {
	goto L199;
    }
    i__1 = *p;
    for (i__ = 1; i__ <= i__1; ++i__) {
	g[i__ + g_dim1] *= cut;
/* L150: */
    }
    goto L60;
/*     -------- */
L140:
    *asr = s;
    cut = 1.;
    i__1 = *p;
    for (i__ = 1; i__ <= i__1; ++i__) {
	a[i__] = g[i__ + (g_dim1 << 1)];
/* L160: */
    }
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	k = (integer) sc[j + sc_dim1];
	t[k] = sc[j + sc_dim1 * 11];
	f[k] = sc[j + sc_dim1 * 12];
/* L170: */
    }
    if (*asr <= 0. || (asrold - *asr) / asrold < bdrz01_1.conv) {
	goto L199;
    }
    if (iter > bdrz01_1.mitone || *p <= 1) {
	goto L199;
    }
    bdrder(n, &sc[sc_dim1 * 11 + 1], &sc[sc_dim1 * 12 + 1], &sc[sc_dim1 * 3 
	    + 1], &bdrz01_1.fdel, &sc[(sc_dim1 << 2) + 1], &sc[sc_dim1 * 5 + 
	    1]);
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	k = (integer) sc[j + sc_dim1];
	sc[j + sc_dim1 * 5] = y[j] - f[j];
	sc[k + sc_dim1 * 6] = sc[j + (sc_dim1 << 2)];
/* L180: */
    }
    bdrdir(p, n, &w[1], sw, &sc[sc_dim1 * 5 + 1], &x[x_offset], &sc[sc_dim1 *
	     6 + 1], &g[g_offset], &dp[1]);
    goto L100;
/* -------------- */
L199:
/* -------------- */
    s = 0.;
    v = s;
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	s += w[j] * f[j];
/* L210: */
    }
    s /= *sw;
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	f[j] -= s;
/* Computing 2nd power */
	d__1 = f[j];
	v += w[j] * (d__1 * d__1);
/* L220: */
    }
    if (v > 0.) {
	v = 1. / sqrt(v / *sw);
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
/* L230: */
	    f[j] *= v;
	}
    }
    return 0;
} /* bdroneone_ */

/* Subroutine */ int bdrdir(integer *p, integer *n, doublereal *w, 
	doublereal *sw, doublereal *r__, doublereal *x, doublereal *d__, 
	doublereal *e, doublereal *g)
{
    /* System generated locals */
    integer x_dim1, x_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k, l;
    static doublereal s;
    static integer m1, m2;
    extern /* Subroutine */ int bdrconj(integer *, doublereal *, doublereal *
	    , doublereal *, doublereal *, integer *, doublereal *);

    /* Parameter adjustments */
    --e;
    --d__;
    x_dim1 = *p;
    x_offset = x_dim1 + 1;
    x -= x_offset;
    --r__;
    --w;
    --g;

    /* Function Body */
    i__1 = *p;
    for (i__ = 1; i__ <= i__1; ++i__) {
	s = 0.;
	i__2 = *n;
	for (j = 1; j <= i__2; ++j) {
	    s += w[j] * d__[j] * x[i__ + j * x_dim1];
/* L11251: */
	}
	e[i__] = s / *sw;
/* L11241: */
    }
    k = 0;
    m1 = *p * (*p + 1) / 2;
    m2 = m1 + *p;
    i__1 = *p;
    for (j = 1; j <= i__1; ++j) {
	s = 0.;
	i__2 = *n;
	for (l = 1; l <= i__2; ++l) {
	    s += w[l] * r__[l] * (d__[l] * x[j + l * x_dim1] - e[j]);
/* L11271: */
	}
	g[m1 + j] = s / *sw;
	i__2 = j;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    s = 0.;
	    i__3 = *n;
	    for (l = 1; l <= i__3; ++l) {
		s += w[l] * (d__[l] * x[i__ + l * x_dim1] - e[i__]) * (d__[l] 
			* x[j + l * x_dim1] - e[j]);
/* L11291: */
	    }
	    ++k;
	    g[k] = s / *sw;
/* L11281: */
	}
/* L11261: */
    }
    bdrconj(p, &g[1], &g[m1 + 1], &g[m2 + 1], &bdrz01_1.cjeps, &
	    bdrz01_1.mitcj, &g[m2 + *p + 1]);
    i__1 = *p;
    for (i__ = 1; i__ <= i__1; ++i__) {
	e[i__] = g[m2 + i__];
/* L11301: */
    }
    return 0;
} /* bdrdir_ */

/* Subroutine */ int bdrconj(integer *p, doublereal *g, doublereal *c__, 
	doublereal *x, doublereal *eps, integer *maxit, doublereal *sc)
{
    /* System generated locals */
    integer sc_dim1, sc_offset, i__1, i__2;
    doublereal d__1, d__2, d__3;

    /* Local variables */
    static doublereal beta;
    static integer iter;
    static doublereal h__;
    static integer i__, j;
    static doublereal s, t, alpha;
    static integer im1, nit;

    /* Parameter adjustments */
    sc_dim1 = *p;
    sc_offset = sc_dim1 + 1;
    sc -= sc_offset;
    --x;
    --c__;
    --g;

    /* Function Body */
    i__1 = *p;
    for (i__ = 1; i__ <= i__1; ++i__) {
	x[i__] = 0.;
	sc[i__ + (sc_dim1 << 1)] = 0.;
/* L11311: */
    }
    nit = 0;
/* REPEAT */
L11321:
    ++nit;
    h__ = 0.;
    beta = 0.;
    i__1 = *p;
    for (i__ = 1; i__ <= i__1; ++i__) {
	sc[i__ + (sc_dim1 << 2)] = x[i__];
	s = g[i__ * (i__ - 1) / 2 + i__] * x[i__];
	im1 = i__ - 1;
	j = 1;
	goto L11343;
L11341:
	++j;
L11343:
	if (j > im1) {
	    goto L11342;
	}
	s += g[i__ * (i__ - 1) / 2 + j] * x[j];
	goto L11341;
L11342:
	j = i__ + 1;
	goto L11353;
L11351:
	++j;
L11353:
	if (j > *p) {
	    goto L11352;
	}
	s += g[j * (j - 1) / 2 + i__] * x[j];
	goto L11351;
L11352:
	sc[i__ + sc_dim1] = s - c__[i__];
/* Computing 2nd power */
	d__1 = sc[i__ + sc_dim1];
	h__ += d__1 * d__1;
/* L11331: */
    }
    if (h__ <= 0.) {
	goto L11322;
    }
    i__1 = *p;
    for (iter = 1; iter <= i__1; ++iter) {
	i__2 = *p;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    sc[i__ + (sc_dim1 << 1)] = beta * sc[i__ + (sc_dim1 << 1)] - sc[
		    i__ + sc_dim1];
/* L11371: */
	}
	t = 0.;
	i__2 = *p;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    s = g[i__ * (i__ - 1) / 2 + i__] * sc[i__ + (sc_dim1 << 1)];
	    im1 = i__ - 1;
	    j = 1;
	    goto L11393;
L11391:
	    ++j;
L11393:
	    if (j > im1) {
		goto L11392;
	    }
	    s += g[i__ * (i__ - 1) / 2 + j] * sc[j + (sc_dim1 << 1)];
	    goto L11391;
L11392:
	    j = i__ + 1;
	    goto L11403;
L11401:
	    ++j;
L11403:
	    if (j > *p) {
		goto L11402;
	    }
	    s += g[j * (j - 1) / 2 + i__] * sc[j + (sc_dim1 << 1)];
	    goto L11401;
L11402:
	    sc[i__ + sc_dim1 * 3] = s;
	    t += s * sc[i__ + (sc_dim1 << 1)];
/* L11381: */
	}
	alpha = h__ / t;
	s = 0.;
	i__2 = *p;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    x[i__] += alpha * sc[i__ + (sc_dim1 << 1)];
	    sc[i__ + sc_dim1] += alpha * sc[i__ + sc_dim1 * 3];
/* Computing 2nd power */
	    d__1 = sc[i__ + sc_dim1];
	    s += d__1 * d__1;
/* L11411: */
	}
	if (s <= 0.) {
	    goto L11362;
	}
	beta = s / h__;
	h__ = s;
/* L11361: */
    }
L11362:
    s = 0.;
    i__1 = *p;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing MAX */
	d__2 = s, d__3 = (d__1 = x[i__] - sc[i__ + (sc_dim1 << 2)], abs(d__1))
		;
	s = max(d__2,d__3);
/* L11421: */
    }
    if (s >= *eps && nit < *maxit) {
	goto L11321;
    }
L11322:
    return 0;
} /* bdrconj_ */

/* Subroutine */ int bdrder(integer *n, doublereal *x, doublereal *s, 
	doublereal *w, doublereal *fdel, doublereal *d__, doublereal *sc)
{
    /* System generated locals */
    integer sc_dim1, sc_offset, i__1;

    /* Local variables */
    static integer i__, j;
    static doublereal scale;
    static integer bc, ec, bl, el, br, er;
    static doublereal del;
    extern /* Subroutine */ int bdrpool(integer *, doublereal *, doublereal *
	    , doublereal *, doublereal *);


/*     unnecessary initialization of bl el ec to keep g77 -Wall happy */

    /* Parameter adjustments */
    sc_dim1 = *n;
    sc_offset = sc_dim1 + 1;
    sc -= sc_offset;
    --d__;
    --w;
    --s;
    --x;

    /* Function Body */
    bl = 0;
    el = 0;
    ec = 0;

    if (x[*n] > x[1]) {
	goto L11441;
    }
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	d__[j] = 0.;
/* L11451: */
    }
    return 0;
L11441:
    i__ = *n / 4;
    j = i__ * 3;
    scale = x[j] - x[i__];
L11461:
    if (scale > 0.) {
	goto L11462;
    }
    if (j < *n) {
	++j;
    }
    if (i__ > 1) {
	--i__;
    }
    scale = x[j] - x[i__];
    goto L11461;
L11462:
    del = *fdel * scale * 2.;
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	sc[j + sc_dim1] = x[j];
	sc[j + (sc_dim1 << 1)] = s[j];
	sc[j + sc_dim1 * 3] = w[j];
/* L11471: */
    }
    bdrpool(n, &sc[sc_offset], &sc[(sc_dim1 << 1) + 1], &sc[sc_dim1 * 3 + 1],
	     &del);
    bc = 0;
    br = bc;
    er = br;
L11481:
    br = er + 1;
    er = br;
L11491:
    if (er >= *n) {
	goto L11492;
    }
    if (sc[br + sc_dim1] != sc[er + 1 + sc_dim1]) {
	goto L11511;
    }
    ++er;
    goto L11521;
L11511:
    goto L11492;
L11521:
/* L11501: */
    goto L11491;
L11492:
    if (br != 1) {
	goto L11541;
    }
    bl = br;
    el = er;
    goto L11481;
L11541:
    if (bc != 0) {
	goto L11561;
    }
    bc = br;
    ec = er;
    i__1 = el;
    for (j = bl; j <= i__1; ++j) {
	d__[j] = (sc[bc + (sc_dim1 << 1)] - sc[bl + (sc_dim1 << 1)]) / (sc[bc 
		+ sc_dim1] - sc[bl + sc_dim1]);
/* L11571: */
    }
    goto L11481;
L11561:
    i__1 = ec;
    for (j = bc; j <= i__1; ++j) {
	d__[j] = (sc[br + (sc_dim1 << 1)] - sc[bl + (sc_dim1 << 1)]) / (sc[br 
		+ sc_dim1] - sc[bl + sc_dim1]);
/* L11581: */
    }
    if (er != *n) {
	goto L11601;
    }
    i__1 = er;
    for (j = br; j <= i__1; ++j) {
	d__[j] = (sc[br + (sc_dim1 << 1)] - sc[bc + (sc_dim1 << 1)]) / (sc[br 
		+ sc_dim1] - sc[bc + sc_dim1]);
/* L11611: */
    }
    goto L11482;
L11601:
    bl = bc;
    el = ec;
    bc = br;
    ec = er;
    goto L11481;
L11482:
    return 0;
} /* bdrder_ */

/* Subroutine */ int bdrpool(integer *n, doublereal *x, doublereal *y, 
	doublereal *w, doublereal *del)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, bb, eb, bl, el, br, er;
    static doublereal pw, px, py;

    /* Parameter adjustments */
    --w;
    --y;
    --x;

    /* Function Body */
    bb = 0;
    eb = bb;
L11621:
    if (eb >= *n) {
	goto L11622;
    }
    bb = eb + 1;
    eb = bb;
L11631:
    if (eb >= *n) {
	goto L11632;
    }
    if (x[bb] != x[eb + 1]) {
	goto L11651;
    }
    ++eb;
    goto L11661;
L11651:
    goto L11632;
L11661:
/* L11641: */
    goto L11631;
L11632:
    if (eb >= *n) {
	goto L11681;
    }
    if (x[eb + 1] - x[eb] >= *del) {
	goto L11701;
    }
    br = eb + 1;
    er = br;
L11711:
    if (er >= *n) {
	goto L11712;
    }
    if (x[er + 1] != x[br]) {
	goto L11731;
    }
    ++er;
    goto L11741;
L11731:
    goto L11712;
L11741:
/* L11721: */
    goto L11711;
L11712:
    if (er < *n && x[er + 1] - x[er] < x[eb + 1] - x[eb]) {
	goto L11621;
    }
    eb = er;
    pw = w[bb] + w[eb];
    px = (x[bb] * w[bb] + x[eb] * w[eb]) / pw;
    py = (y[bb] * w[bb] + y[eb] * w[eb]) / pw;
    i__1 = eb;
    for (i__ = bb; i__ <= i__1; ++i__) {
	x[i__] = px;
	y[i__] = py;
	w[i__] = pw;
/* L11751: */
    }
L11701:
L11681:
L11761:
    if (bb <= 1) {
	goto L11762;
    }
    if (x[bb] - x[bb - 1] >= *del) {
	goto L11762;
    }
    bl = bb - 1;
    el = bl;
L11771:
    if (bl <= 1) {
	goto L11772;
    }
    if (x[bl - 1] != x[el]) {
	goto L11791;
    }
    --bl;
    goto L11801;
L11791:
    goto L11772;
L11801:
/* L11781: */
    goto L11771;
L11772:
    bb = bl;
    pw = w[bb] + w[eb];
    px = (x[bb] * w[bb] + x[eb] * w[eb]) / pw;
    py = (y[bb] * w[bb] + y[eb] * w[eb]) / pw;
    i__1 = eb;
    for (i__ = bb; i__ <= i__1; ++i__) {
	x[i__] = px;
	y[i__] = py;
	w[i__] = pw;
/* L11811: */
    }
    goto L11761;
L11762:
    goto L11621;
L11622:
    return 0;
} /* bdrpool_ */

/* Subroutine */ int bdrnewb(integer *lm, integer *q, doublereal *ww, 
	doublereal *b)
{
    /* System generated locals */
    integer b_dim1, b_offset, i__1, i__2;
    doublereal d__1;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static integer i__, l;
    static doublereal s, t;
    static integer l1, lm1;
    static doublereal sml;

    /* Parameter adjustments */
    b_dim1 = *q;
    b_offset = b_dim1 + 1;
    b -= b_offset;
    --ww;

    /* Function Body */
    sml = 1. / bdrparms_1.big;
    if (*q != 1) {
	goto L11831;
    }
    b[*lm * b_dim1 + 1] = 1.;
    return 0;
L11831:
    if (*lm != 1) {
	goto L11851;
    }
    i__1 = *q;
    for (i__ = 1; i__ <= i__1; ++i__) {
	b[i__ + *lm * b_dim1] = (doublereal) i__;
/* L11861: */
    }
    return 0;
L11851:
    lm1 = *lm - 1;
    i__1 = *q;
    for (i__ = 1; i__ <= i__1; ++i__) {
	b[i__ + *lm * b_dim1] = 0.;
/* L11871: */
    }
    t = 0.;
    i__1 = *q;
    for (i__ = 1; i__ <= i__1; ++i__) {
	s = 0.;
	i__2 = lm1;
	for (l = 1; l <= i__2; ++l) {
	    s += (d__1 = b[i__ + l * b_dim1], abs(d__1));
/* L11891: */
	}
	b[i__ + *lm * b_dim1] = s;
	t += s;
/* L11881: */
    }
    i__1 = *q;
    for (i__ = 1; i__ <= i__1; ++i__) {
	b[i__ + *lm * b_dim1] = ww[i__] * (t - b[i__ + *lm * b_dim1]);
/* L11901: */
    }
    l1 = 1;
    if (*lm > *q) {
	l1 = *lm - *q + 1;
    }
    i__1 = lm1;
    for (l = l1; l <= i__1; ++l) {
	s = 0.;
	t = s;
	i__2 = *q;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    s += ww[i__] * b[i__ + *lm * b_dim1] * b[i__ + l * b_dim1];
/* Computing 2nd power */
	    d__1 = b[i__ + l * b_dim1];
	    t += ww[i__] * (d__1 * d__1);
/* L11921: */
	}
	s /= sqrt(t);
	i__2 = *q;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    b[i__ + *lm * b_dim1] -= s * b[i__ + l * b_dim1];
/* L11931: */
	}
/* L11911: */
    }
    i__1 = *q;
    for (i__ = 2; i__ <= i__1; ++i__) {
	if ((d__1 = b[i__ - 1 + *lm * b_dim1] - b[i__ + *lm * b_dim1], abs(
		d__1)) > sml) {
	    return 0;
	}
/* L11941: */
    }
    i__1 = *q;
    for (i__ = 1; i__ <= i__1; ++i__) {
	b[i__ + *lm * b_dim1] = (doublereal) i__;
/* L11951: */
    }
    return 0;
} /* bdrnewb_ */

/* Subroutine */ int bdrbkppr(void)
{
    return 0;
} /* bdrbkppr_ */


/* Subroutine */ int bdrsetppr(doublereal *span1, doublereal *alpha1, 
	integer *optlevel, integer *ism, doublereal *df1, doublereal *gcvpen1)
{
/* Put `parameters' into Common blocks */
    bdrparms_1.span = *span1;
    bdrparms_1.lf = *optlevel;
    bdrparms_1.alpha = *alpha1;
    bdrspsmooth_1.ismethod = *ism;
    bdrspsmooth_1.df = *df1;
    bdrspsmooth_1.gcvpen = *gcvpen1;
    return 0;
} /* bdrsetppr_ */

/* Subroutine */ int bdrfsort(integer *mu, integer *n, doublereal *f, 
	doublereal *t, doublereal *sp)
{
    /* System generated locals */
    integer f_dim1, f_offset, t_dim1, t_offset, sp_dim1, sp_offset, i__1, 
	    i__2;

    /* Local variables */
    static integer j, k, l;
    extern /* Subroutine */ int bdrsort(doublereal *, doublereal *, integer *
	    , integer *);



    /* Parameter adjustments */
    sp_dim1 = *n;
    sp_offset = sp_dim1 + 1;
    sp -= sp_offset;
    t_dim1 = *n;
    t_offset = t_dim1 + 1;
    t -= t_offset;
    f_dim1 = *n;
    f_offset = f_dim1 + 1;
    f -= f_offset;

    /* Function Body */
    i__1 = *mu;
    for (l = 1; l <= i__1; ++l) {
	i__2 = *n;
	for (j = 1; j <= i__2; ++j) {
	    sp[j + sp_dim1] = j + .1f;
	    sp[j + (sp_dim1 << 1)] = f[j + l * f_dim1];
/* L10: */
	}
	bdrsort(&t[l * t_dim1 + 1], &sp[sp_offset], &c__1, n);
	i__2 = *n;
	for (j = 1; j <= i__2; ++j) {
	    k = (integer) sp[j + sp_dim1];
	    f[j + l * f_dim1] = sp[k + (sp_dim1 << 1)];
/* L20: */
	}
/* L100: */
    }
    return 0;
} /* bdrfsort_ */

/* Subroutine */ int bdrpred(integer *np, doublereal *x, doublereal *smod, 
	doublereal *y, doublereal *sc)
{
    /* System generated locals */
    integer x_dim1, x_offset, y_dim1, y_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer high;
    extern /* Subroutine */ int bdrfsort(integer *, integer *, doublereal *, 
	    doublereal *, doublereal *);
    static integer i__, j, l, m, n, p, q;
    static doublereal s;
    static integer place;
    static doublereal t;
    static integer ja, jb, jf, jt, mu;
    static doublereal ys;
    static integer jfh, jfl, jth, inp, jtl, low;

    /* Parameter adjustments */
    y_dim1 = *np;
    y_offset = y_dim1 + 1;
    y -= y_offset;
    x_dim1 = *np;
    x_offset = x_dim1 + 1;
    x -= x_offset;
    --smod;
    --sc;

    /* Function Body */
    m = (integer) (smod[1] + .1f);
    p = (integer) (smod[2] + .1f);
    q = (integer) (smod[3] + .1f);
    n = (integer) (smod[4] + .1f);
    mu = (integer) (smod[5] + .1f);
    ys = smod[q + 6];
    ja = q + 6;
    jb = ja + p * m;
    jf = jb + m * q;
    jt = jf + n * m;
    bdrfsort(&mu, &n, &smod[jf + 1], &smod[jt + 1], &sc[1]);
    i__1 = *np;
    for (inp = 1; inp <= i__1; ++inp) {
	ja = q + 6;
	jb = ja + p * m;
	jf = jb + m * q;
	jt = jf + n * m;
	i__2 = q;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    y[inp + i__ * y_dim1] = 0.;
/* L81: */
	}
	i__2 = mu;
	for (l = 1; l <= i__2; ++l) {
	    s = 0.;
	    i__3 = p;
	    for (j = 1; j <= i__3; ++j) {
		s += smod[ja + j] * x[inp + j * x_dim1];
/* L12201: */
	    }
	    if (s > smod[jt + 1]) {
		goto L12221;
	    }
	    place = 1;
	    goto L12230;
L12221:
	    if (s < smod[jt + n]) {
		goto L12251;
	    }
	    place = n;
	    goto L12230;
L12251:
	    low = 0;
	    high = n + 1;
/* 	 WHILE */
L12261:
	    if (low + 1 >= high) {
		goto L12262;
	    }
	    place = (low + high) / 2;
	    t = smod[jt + place];
	    if (s == t) {
		goto L12230;
	    }
	    if (s < t) {
		high = place;
	    } else {
		low = place;
	    }
	    goto L12261;
/* 	 END */
L12262:
	    jfl = jf + low;
	    jfh = jf + high;
	    jtl = jt + low;
	    jth = jt + high;
	    t = smod[jfl] + (smod[jfh] - smod[jfl]) * (s - smod[jtl]) / (smod[
		    jth] - smod[jtl]);
	    goto L12300;
L12230:
	    t = smod[jf + place];
L12300:
	    i__3 = q;
	    for (i__ = 1; i__ <= i__3; ++i__) {
		y[inp + i__ * y_dim1] += smod[jb + i__] * t;
/* L12311: */
	    }
	    ja += p;
	    jb += q;
	    jf += n;
	    jt += n;
/* L91: */
	}
	i__2 = q;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    y[inp + i__ * y_dim1] = ys * y[inp + i__ * y_dim1] + smod[i__ + 5]
		    ;
/* L12321: */
	}
/* L100: */
    }
    return 0;
} /* bdrpred_ */

/* Subroutine */ int bdrsetsmu(void)
{
    bdrspsmooth_1.ismethod = 0;
    return 0;
} /* bdrsetsmu_ */

/* Subroutine */ int bdrsupsmu(integer *n, doublereal *x, doublereal *y, 
	doublereal *w, integer *iper, doublereal *span, doublereal *alpha, 
	doublereal *smo, doublereal *sc, doublereal *edf)
{
    /* System generated locals */
    integer sc_dim1, sc_offset, i__1;
    doublereal d__1, d__2, d__3, d__4;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer jper;
    static doublereal a, f, h__;
    static integer i__, j;
    static doublereal scale;
    extern /* Subroutine */ int bdrspline(integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *), 
	    bdrsmooth(integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *)
	    ;
    static doublereal sw, sy, resmin, vsmlsq;


/* ------------------------------------------------------------------ */

/* super smoother (Friedman, 1984). */

/* version 10/10/84 */

/* coded	 and copywrite (c) 1984 by: */

/* 			 Jerome H. Friedman */
/* 		      department of statistics */
/* 				and */
/* 		 stanford linear accelerator center */
/* 			 stanford university */

/* all rights reserved. */


/* input: */
/*    n : number of observations (x,y - pairs). */
/*    x(n) : ordered abscissa values. */
/*    y(n) : corresponding ordinate (response) values. */
/*    w(n) : weight for each (x,y) observation. */
/*    iper : periodic variable flag. */
/* 	iper=1 => x is ordered interval variable. */
/* 	iper=2 => x is a periodic variable with values */
/* 		  in the range (0.0,1.0) and period 1.0. */
/*    span : smoother span (fraction of observations in window). */
/* 	    span=0.0 => automatic (variable) span selection. */
/*    alpha : controls high frequency (small span) penality */
/* 	     used with automatic span selection (bass tone control). */
/* 	     (alpha.le.0.0 or alpha.gt.10.0 => no effect.) */
/* output: */
/*   smo(n) : smoothed ordinate (response) values. */
/* scratch: */
/*   sc(n,7) : internal working storage. */

/* note: */
/*    for small samples (n < 40) or if there are substantial serial */
/*    correlations between observations close in x - value, then */
/*    a prespecified fixed span smoother (span > 0) should be */
/*    used. reasonable span values are 0.2 to 0.4. */

/* ------------------------------------------------------------------ */

    /* Parameter adjustments */
    sc_dim1 = *n;
    sc_offset = sc_dim1 + 1;
    sc -= sc_offset;
    --smo;
    --w;
    --y;
    --x;

    /* Function Body */
    if (x[*n] > x[1]) {
	goto L30;
    }
    sy = 0.;
    sw = sy;
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	sy += w[j] * y[j];
	sw += w[j];
/* L10: */
    }
    a = 0.;
    if (sw > 0.) {
	a = sy / sw;
    }
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	smo[j] = a;
/* L20: */
    }
    return 0;
L30:
/*     change by BDR */
    if (bdrspsmooth_1.ismethod != 0) {
	bdrspline(n, &x[1], &y[1], &w[1], &smo[1], edf);
    } else {
	i__ = *n / 4;
	j = i__ * 3;
	scale = x[j] - x[i__];
L40:
	if (scale > 0.) {
	    goto L50;
	}
	if (j < *n) {
	    ++j;
	}
	if (i__ > 1) {
	    --i__;
	}
	scale = x[j] - x[i__];
	goto L40;
L50:
/* Computing 2nd power */
	d__1 = bdrconsts_1.eps * scale;
	vsmlsq = d__1 * d__1;
	jper = *iper;
	if (*iper == 2 && (x[1] < 0. || x[*n] > 1.)) {
	    jper = 1;
	}
	if (jper < 1 || jper > 2) {
	    jper = 1;
	}
	if (*span <= 0.) {
	    goto L60;
	}
	bdrsmooth(n, &x[1], &y[1], &w[1], span, &jper, &vsmlsq, &smo[1], &sc[
		sc_offset]);
	return 0;
L60:
	for (i__ = 1; i__ <= 3; ++i__) {
	    bdrsmooth(n, &x[1], &y[1], &w[1], &bdrspans_1.spans[i__ - 1], &
		    jper, &vsmlsq, &sc[((i__ << 1) - 1) * sc_dim1 + 1], &sc[
		    sc_dim1 * 7 + 1]);
	    i__1 = -jper;
	    bdrsmooth(n, &x[1], &sc[sc_dim1 * 7 + 1], &w[1], &
		    bdrspans_1.spans[1], &i__1, &vsmlsq, &sc[(i__ << 1) * 
		    sc_dim1 + 1], &h__);
/* L70: */
	}
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    resmin = bdrconsts_1.big;
	    for (i__ = 1; i__ <= 3; ++i__) {
		if (sc[j + (i__ << 1) * sc_dim1] >= resmin) {
		    goto L80;
		}
		resmin = sc[j + (i__ << 1) * sc_dim1];
		sc[j + sc_dim1 * 7] = bdrspans_1.spans[i__ - 1];
L80:
		;
	    }
	    if (*alpha > 0. && *alpha <= 10. && resmin < sc[j + sc_dim1 * 6] 
		    && resmin > 0.) {
/* Computing MAX */
		d__2 = bdrconsts_1.sml, d__3 = resmin / sc[j + sc_dim1 * 6];
		d__1 = max(d__2,d__3);
		d__4 = 10. - *alpha;
		sc[j + sc_dim1 * 7] += (bdrspans_1.spans[2] - sc[j + sc_dim1 *
			 7]) * pow_dd(&d__1, &d__4);
	    }
/* L90: */
	}
	i__1 = -jper;
	bdrsmooth(n, &x[1], &sc[sc_dim1 * 7 + 1], &w[1], &bdrspans_1.spans[1]
		, &i__1, &vsmlsq, &sc[(sc_dim1 << 1) + 1], &h__);
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    if (sc[j + (sc_dim1 << 1)] <= bdrspans_1.spans[0]) {
		sc[j + (sc_dim1 << 1)] = bdrspans_1.spans[0];
	    }
	    if (sc[j + (sc_dim1 << 1)] >= bdrspans_1.spans[2]) {
		sc[j + (sc_dim1 << 1)] = bdrspans_1.spans[2];
	    }
	    f = sc[j + (sc_dim1 << 1)] - bdrspans_1.spans[1];
	    if (f >= 0.) {
		goto L100;
	    }
	    f = -f / (bdrspans_1.spans[1] - bdrspans_1.spans[0]);
	    sc[j + (sc_dim1 << 2)] = (1. - f) * sc[j + sc_dim1 * 3] + f * sc[
		    j + sc_dim1];
	    goto L110;
L100:
	    f /= bdrspans_1.spans[2] - bdrspans_1.spans[1];
	    sc[j + (sc_dim1 << 2)] = (1. - f) * sc[j + sc_dim1 * 3] + f * sc[
		    j + sc_dim1 * 5];
L110:
	    ;
	}
	i__1 = -jper;
	bdrsmooth(n, &x[1], &sc[(sc_dim1 << 2) + 1], &w[1], bdrspans_1.spans,
		 &i__1, &vsmlsq, &smo[1], &h__);
	*edf = 0.;
    }
    return 0;
} /* bdrsupsmu_ */

/* Subroutine */ int bdrsmooth(integer *n, doublereal *x, doublereal *y, 
	doublereal *w, doublereal *span, integer *iper, doublereal *vsmlsq, 
	doublereal *smo, doublereal *acvr)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Local variables */
    static doublereal cvar;
    static integer jper;
    static doublereal a, h__;
    static integer i__, j, j0, in, it;
    static doublereal xm, ym, wt, sy, fbo, fbw;
    static integer ibw;
    static doublereal var, tmp, xti;
    static integer out;
    static doublereal xto;

    /* Parameter adjustments */
    --acvr;
    --smo;
    --w;
    --y;
    --x;

    /* Function Body */
    xm = 0.;
    ym = xm;
    var = ym;
    cvar = var;
    fbw = cvar;
    jper = abs(*iper);
    ibw = (integer) (*span * .5f * *n + .5f);
    if (ibw < 2) {
	ibw = 2;
    }
    it = (ibw << 1) + 1;
    i__1 = it;
    for (i__ = 1; i__ <= i__1; ++i__) {
	j = i__;
	if (jper == 2) {
	    j = i__ - ibw - 1;
	}
	xti = x[j];
	if (j >= 1) {
	    goto L10;
	}
	j = *n + j;
	xti = x[j] - 1.;
L10:
	wt = w[j];
	fbo = fbw;
	fbw += wt;
	if (fbw > 0.) {
	    xm = (fbo * xm + wt * xti) / fbw;
	}
	if (fbw > 0.) {
	    ym = (fbo * ym + wt * y[j]) / fbw;
	}
	tmp = 0.;
	if (fbo > 0.) {
	    tmp = fbw * wt * (xti - xm) / fbo;
	}
	var += tmp * (xti - xm);
	cvar += tmp * (y[j] - ym);
/* L20: */
    }
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	out = j - ibw - 1;
	in = j + ibw;
	if (jper != 2 && (out < 1 || in > *n)) {
	    goto L60;
	}
	if (out >= 1) {
	    goto L30;
	}
	out = *n + out;
	xto = x[out] - 1.;
	xti = x[in];
	goto L50;
L30:
	if (in <= *n) {
	    goto L40;
	}
	in -= *n;
	xti = x[in] + 1.;
	xto = x[out];
	goto L50;
L40:
	xto = x[out];
	xti = x[in];
L50:
	wt = w[out];
	fbo = fbw;
	fbw -= wt;
	tmp = 0.;
	if (fbw > 0.) {
	    tmp = fbo * wt * (xto - xm) / fbw;
	}
	var -= tmp * (xto - xm);
	cvar -= tmp * (y[out] - ym);
	if (fbw > 0.) {
	    xm = (fbo * xm - wt * xto) / fbw;
	}
	if (fbw > 0.) {
	    ym = (fbo * ym - wt * y[out]) / fbw;
	}
	wt = w[in];
	fbo = fbw;
	fbw += wt;
	if (fbw > 0.) {
	    xm = (fbo * xm + wt * xti) / fbw;
	}
	if (fbw > 0.) {
	    ym = (fbo * ym + wt * y[in]) / fbw;
	}
	tmp = 0.;
	if (fbo > 0.) {
	    tmp = fbw * wt * (xti - xm) / fbo;
	}
	var += tmp * (xti - xm);
	cvar += tmp * (y[in] - ym);
L60:
	a = 0.;
	if (var > *vsmlsq) {
	    a = cvar / var;
	}
	smo[j] = a * (x[j] - xm) + ym;
	if (*iper <= 0) {
	    goto L80;
	}
	h__ = 0.;
	if (fbw > 0.) {
	    h__ = 1. / fbw;
	}
	if (var > *vsmlsq) {
/* Computing 2nd power */
	    d__1 = x[j] - xm;
	    h__ += d__1 * d__1 / var;
	}
	acvr[j] = 0.;
	a = 1. - w[j] * h__;
	if (a <= 0.) {
	    goto L70;
	}
	acvr[j] = (d__1 = y[j] - smo[j], abs(d__1)) / a;
	goto L80;
L70:
	if (j <= 1) {
	    goto L80;
	}
	acvr[j] = acvr[j - 1];
L80:
	;
    }
    j = 1;
/* -- */
L90:
    j0 = j;
    sy = smo[j] * w[j];
    fbw = w[j];
    if (j >= *n) {
	goto L110;
    }
L100:
    if (x[j + 1] > x[j]) {
	goto L110;
    }
    ++j;
    sy += w[j] * smo[j];
    fbw += w[j];
    if (j < *n) {
	goto L100;
    }
L110:
    if (j <= j0) {
	goto L130;
    }
    a = 0.;
    if (fbw > 0.) {
	a = sy / fbw;
    }
    i__1 = j;
    for (i__ = j0; i__ <= i__1; ++i__) {
	smo[i__] = a;
/* L120: */
    }
L130:
    ++j;
    if (j <= *n) {
	goto L90;
    }
    return 0;
} /* bdrsmooth_ */

/* Subroutine */ int bdrbksupsmu(void)
{
    return 0;
} /* bdrbksupsmu_ */


/* --------------------------------------------------------------- */

/* this sets the compile time (default) values for various */
/* internal parameters : */

/* spans : span values for the three running linear smoothers. */
/* spans(1) : tweeter span. */
/* spans(2) : midrange span. */
/* spans(3) : woofer span. */
/* (these span values should be changed only with care.) */
/* big : a large representable floating point number. */
/* sml : a small number. should be set so that (sml)**(10.0) does */
/* 	not cause floating point underflow. */
/* eps : used to numerically stabilize slope calculations for */
/* 	running linear fits. */

/* these parameter values can be changed by declaring the */
/* relevant labeled common in the main program and resetting */
/* them with executable statements. */

/* ----------------------------------------------------------------- */


/* Subroutine */ int bdrspline(integer *n, doublereal *x, doublereal *y, 
	doublereal *w, doublereal *smo, doublereal *edf)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static doublereal coef[25], crit, dsmo[2500], knot[29], work[1050];
    static integer i__;
    static doublereal p, s, param[3];
    extern /* Subroutine */ int intpr(char *, integer *, integer *, integer *), 
      bdrsplerr(void);
//    extern /* Subroutine */ int intpr(char *, integer *, integer *, integer *
//	    , ftnlen), bdrsplerr(void);
    static doublereal lambda;
    static integer nk, ip;
    static doublereal dw[2500], dx[2500], dy[2500];
//    extern /* Subroutine */ int dblepr(char *, integer *, doublereal *, 
//	    integer *, ftnlen);
    extern /* Subroutine */ int dblepr0(char *, integer *, doublereal *, 
	    integer *);
    static doublereal df1;
    extern /* Subroutine */ int qsbart(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, real *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, integer *, doublereal *, doublereal *, integer *, 
	    doublereal *, integer *, integer *, integer *);
    static integer isetup, ier, par[2];
    static doublereal lev[2500];


/* ------------------------------------------------------------------ */

/* input: */
/*    n : number of observations. */
/*    x(n) : ordered abscissa values. */
/*    y(n) : corresponding ordinate (response) values. */
/*    w(n) : weight for each (x,y) observation. */
/* output: */
/*   smo(n) : smoothed ordinate (response) values. */
/*   edf : equivalent degrees of freedom */

/* ------------------------------------------------------------------ */

    /* Parameter adjustments */
    --smo;
    --w;
    --y;
    --x;

    /* Function Body */
    if (*n > 2500) {
	bdrsplerr();
    }
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	dx[i__ - 1] = (x[i__] - x[1]) / (x[*n] - x[1]);
	dy[i__ - 1] = y[i__];
/* L10: */
	dw[i__ - 1] = w[i__];
    }
    nk = min(*n,15);
    knot[0] = dx[0];
    knot[1] = dx[0];
    knot[2] = dx[0];
    knot[3] = dx[0];
    knot[nk] = dx[*n - 1];
    knot[nk + 1] = dx[*n - 1];
    knot[nk + 2] = dx[*n - 1];
    knot[nk + 3] = dx[*n - 1];
    i__1 = nk;
    for (i__ = 5; i__ <= i__1; ++i__) {
	p = (*n - 1) * (real) (i__ - 4) / (real) (nk - 3);
	ip = (integer) p;
	p -= ip;
	knot[i__ - 1] = (1 - p) * dx[ip] + p * dx[ip + 1];
/* L40: */
    }
/*      call dblepr('knots', 5, knot, nk+4) */
/* 	par = (icrit, ispar) */
    if (abs(bdrspsmooth_1.ismethod) == 1) {
	par[0] = 3;
	df1 = bdrspsmooth_1.df;
    } else {
	par[0] = 1;
	df1 = 0.;
    }
    par[1] = 0;
    param[0] = 0.;
    param[1] = 1.5;
    param[2] = .01;
    isetup = 0;
    ier = 1;
    qsbart(&bdrspsmooth_1.gcvpen, &df1, dx, dy, dw, &c_b213, n, knot, &nk, 
	    coef, dsmo, lev, &crit, par, &lambda, param, &isetup, work, &c__4,
	     &c__1, &ier);
    if (ier > 0) {
	intpr0("TROUBLE:", &c__8, &ier, &c__1);
    }
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L50: */
	smo[i__] = dsmo[i__ - 1];
    }
/*      call dblepr('smoothed',8, dsmo, n) */
    s = 0.;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L60: */
	s += lev[i__ - 1];
    }
    *edf = s;
    if (bdrspsmooth_1.ismethod < 0) {
	dblepr0("lambda", &c__6, &lambda, &c__1);
	dblepr0("df", &c__2, &s, &c__1);
    }
    return 0;
} /* bdrspline_ */

/* ********************************************************************** */
/* === This was 'sort()' in  gamfit's  mysort.f  [or sortdi() in sortdi.f ] : */

/* ===  FIXME:  Translate to C and add to ../../../main/sort.c <<<<< */


/* why on earth	is a[] double precision ???? */
/* Subroutine */ int bdrsort(doublereal *v, doublereal *a, integer *ii, 
	integer *jj)
{
    static integer i__, j, k, l, m, t, ij, il[20], iu[20], tt;
    static doublereal vt, vtt;


/*     puts into a the permutation vector which sorts v into */
/*     increasing order.	 only elements from ii to jj are considered. */
/*     arrays iu(k) and il(k) permit sorting up to 2**(k+1)-1 elements */

/*     this is a modification of CACM algorithm #347 by R. C. Singleton, */
/*     which is a modified Hoare quicksort. */

    /* Parameter adjustments */
    --v;
    --a;

    /* Function Body */
    m = 1;
    i__ = *ii;
    j = *jj;
L10:
    if (i__ >= j) {
	goto L80;
    }
L20:
    k = i__;
    ij = (j + i__) / 2;
    t = (integer) a[ij];
    vt = v[ij];
    if (v[i__] <= vt) {
	goto L30;
    }
    a[ij] = a[i__];
    a[i__] = (doublereal) t;
    t = (integer) a[ij];
    v[ij] = v[i__];
    v[i__] = vt;
    vt = v[ij];
L30:
    l = j;
    if (v[j] >= vt) {
	goto L50;
    }
    a[ij] = a[j];
    a[j] = (doublereal) t;
    t = (integer) a[ij];
    v[ij] = v[j];
    v[j] = vt;
    vt = v[ij];
    if (v[i__] <= vt) {
	goto L50;
    }
    a[ij] = a[i__];
    a[i__] = (doublereal) t;
    t = (integer) a[ij];
    v[ij] = v[i__];
    v[i__] = vt;
    vt = v[ij];
    goto L50;
L40:
    a[l] = a[k];
    a[k] = (doublereal) tt;
    v[l] = v[k];
    v[k] = vtt;
L50:
    --l;
    if (v[l] > vt) {
	goto L50;
    }
    tt = (integer) a[l];
    vtt = v[l];
L60:
    ++k;
    if (v[k] < vt) {
	goto L60;
    }
    if (k <= l) {
	goto L40;
    }
    if (l - i__ <= j - k) {
	goto L70;
    }
    il[m - 1] = i__;
    iu[m - 1] = l;
    i__ = k;
    ++m;
    goto L90;
L70:
    il[m - 1] = k;
    iu[m - 1] = j;
    j = l;
    ++m;
    goto L90;
L80:
    --m;
    if (m == 0) {
	return 0;
    }
    i__ = il[m - 1];
    j = iu[m - 1];
L90:
    if (j - i__ > 10) {
	goto L20;
    }
    if (i__ == *ii) {
	goto L10;
    }
    --i__;
L100:
    ++i__;
    if (i__ == j) {
	goto L80;
    }
    t = (integer) a[i__ + 1];
    vt = v[i__ + 1];
    if (v[i__] <= vt) {
	goto L100;
    }
    k = i__;
L110:
    a[k + 1] = a[k];
    v[k + 1] = v[k];
    --k;
    if (vt < v[k]) {
	goto L110;
    }
    a[k + 1] = (doublereal) t;
    v[k + 1] = vt;
    goto L100;
} /* bdrsort_ */
