// AlignPair.cpp : Defines the entry point for the console application.

#include "SiftFeature.h"
#include "Homography.h"
#include <time.h>
#include <algorithm>
using namespace std;

void RansacHomography( CHomography& homo, 
					  const MatchArray& aryMatch, 
					  const CFeatureArray& set1, 
					  const CFeatureArray& set2, 
					  float inlierTol, int numIter );

int main(int argc, char* argv[])
{
	int i = -1;
	int j = -1;
	float inlierTol = 1;
	int numIter = 1000;

	// ransac
	srand( time(NULL) );

	int arg = 0;
	while( ++arg < argc) 
	{ 
		if( !strcmp(argv[arg], "-i") )
			i = atoi( argv[++arg] );

		if( !strcmp(argv[arg], "-j") )
			j = atoi( argv[++arg] );

		if( !strcmp(argv[arg], "-tol") )
			inlierTol = atof( argv[++arg] );

		if( !strcmp(argv[arg], "-iter") )
			numIter = atoi( argv[++arg] );
	}	

	try
	{
		char strBuf[128];

		// Step 1: load the extracted features
		CFeatureArray set_i, set_j;
		
		sprintf( strBuf, "%04d.key", i );
		LoadSiftFromFile( set_i, strBuf );
		
		sprintf( strBuf, "%04d.key", j );
		LoadSiftFromFile( set_j, strBuf );

		// Step 2: load the matches
		MatchArray aryMatch;
		LoadMatchArray( aryMatch, i, j );

		// Step 3: Estimate the homography
		CHomography homo;
		RansacHomography( homo, aryMatch, set_i, set_j, inlierTol, numIter );

		// Step 4: Save the homography
		SaveHomography( homo, i, j );
	}
	catch( exception& err )
	{
		printf( "%s\n", err.what() );
	}

	return 0;
}

/**
 *	RansacHomography:
 *		Input:
 *			aryMatch - an array of potential matches between two images
 *			inlierTol - the tolerance to regard a match as an inlier
 *			numIter - number of iterations for Ransac
 *
 *		Ouput:
 *			homo - the best estimated homography (with the max nubmer of inliers)
 */
void RansacHomography( CHomography& homo, 
					  const MatchArray& aryMatch, 
					  const CFeatureArray& set1, 
					  const CFeatureArray& set2, 
					  float inlierTol, int numIter )
{
	const float SQR_TOL = inlierTol*inlierTol;
	const int NUM_SAMP = 6;
	int maxInlier = 0;

	double dA[ NUM_SAMP*2*8 ];
	double dB[ NUM_SAMP*2 ];
	
	// ToDo2: Find homography using RANSAC
	
	printf( "homography inliers: %d(%d)\n", maxInlier, aryMatch.size() );
}