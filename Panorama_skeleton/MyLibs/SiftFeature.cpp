#include "SiftFeature.h"
#include <fstream>

CSiftFeature::CSiftFeature( int numDim )
{
	m_numDim = numDim;
	d = new float[ m_numDim ];
}

CSiftFeature::~CSiftFeature(void)
{
	delete [] d;
}

void LoadSiftFromFile( CFeatureArray& fs, const char* strFileName )
{
	// Open the file.
	ifstream in( strFileName );

	if (!in.is_open())
		throw exception( "File not found in LoadSiftFromFile()" );

	int numFeatures, numDim;
	in >> numFeatures >> numDim;

	fs.resize( numFeatures );

	for( int i=0; i<numFeatures; ++i )
	{
		CSiftFeature* ft = new CSiftFeature( numDim );

		in >> ft->y >> ft->x >> ft->m_scale >> ft->m_angle;

		for( int j=0; j<numDim; ++j )
			in >> ft->d[j];
	
		fs[i] = ft;
	}
}


int FindMatch( const CFeature* ft, const CFeatureArray& set )
{
// ToDo 1: Fill out this function
	return 0;
}

void MatchSiftFeatures( MatchArray& aryMatch, const CFeatureArray& set1, const CFeatureArray& set2 )
{
	aryMatch.resize( set1.size() );
	int num = 0;

	// for each feature in set1
	for( int i=0; i<(int)set1.size(); ++i )
	{
		if( i%100 == 0 )
			printf( "%d / %d\n", i, set1.size() );
		//
		const CSiftFeature* ft1 = dynamic_cast< const CSiftFeature* >( set1[i] );
		
		int j = FindMatch( ft1, set2 );
		int k = FindMatch( set2[j], set1 );	

		bool bQualMatch = false;
		
		if( i==k )
			bQualMatch = true;
		
		// TODO: Find the best match for ft1 in set2.
		//       The quality of a match can be evaluated. We only 
		//       collect matches of good qualities.
		
		if( bQualMatch )
			aryMatch[ num++ ] = make_pair( i, j );
	}

	aryMatch.resize( num );
}