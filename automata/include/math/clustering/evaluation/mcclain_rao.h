//
// Created by jakub on 11/14/15.
//

#ifndef AC_MCCLAIN_RAO_H
#define AC_MCCLAIN_RAO_H

#include "point.h"
#include "kmeans.h"

/*
 * This class evaluates the data for clustering. Namely it tries to
 * find the optimal number of clusters in the given data set.
 * The clustering tool used is KMeans algorithm.
 *
 * Formally McClain-Rao (mc-r) index C is the:
 * Quotient between the mean within-cluster and between-cluster distances.
 * C = (Sw / Nw) / (Sb / Nb) = (Nb / Nw) * (Sw/Sb)
 *
 * ---------------------------------------------------------------------------
 *
 * Sw - the sum of the within-cluster distances
 *   For each cluster k
 *      For each two observations in cluster k, Oi and Oj.
 *           Sw += d(Oi, Oj),
 *            where d is the distance between two observations.
 *
 *  Nw - Total number of distances between
 *  pairs of points belonging to the same cluster.
 * ---------------------------------------------------------------------------
 *
 * Sb - The sum of between-cluster distances
 *   For each distinct pair of clusters k, k'
 *       For each two observations Oi in k and Oj in k'
 *          Sb += d(Oi, Oj)
 *
 * Nb - Total number of distances between pairs of points which do not belong
 * to the same cluster.
 * Nb = N(N-1)/2 - Nw
 *
 * ---------------------------------------------------------------------------
 *
 * The smaller value of index C the better clustering.
 */
template <class T>
class McClainRao {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    // The number of clusters to start evaluating from
    int start_k;
    // The number of clusters to end evaluating.
    int end_k;

    // Point to the data to be evaluated.
    const std::vector<Point<T>>* data;

    // The clustering tool
    KMeans<T>* km;

    // The kmeans clustering with the best mc-r index
    KMeans<T>* best_km;

    // Best index value so far
    double best_C;

    // Total number of distances between
    // pairs of points belonging to the same cluster.
    int nw;

    // the sum of the within-cluster distances
    double sumWithin;

    // Total number of distances between pairs of
    // points which do not belong to the same cluster.
    int nb;

    // The sum of between-cluster distances
    double sumBetween;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

    /*
     * Computes the Sum of the within-cluster distances.
     */
    void computeSumWithin();

    /*
     * Computes the sum of the between-cluster distances
     */
    void computeSumBetween();

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    McClainRao(int start_k, int end_k);

    ~McClainRao();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    /*
     * Computes the McClain-Rao index
     */
    void compute(const std::vector<Point<T>>* data);
};


#endif //AC_MCCLAIN_RAO_H
