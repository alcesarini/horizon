/**
FILE NAME=hl_multiArray.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131228
*/
#ifndef _hl_multiArray_h_
#define _hl_multiArray_h_

#include <hl/basicFiles/hl_workingIncludes.h>


namespace HorizonLib
{
namespace HL_Containers
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MultiIndexHelper
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131227
\brief Helper class for multi-dimensional collection book-keeping.
*/
class HL_MultiIndexHelper : public virtual HLSER::HL_Serializable, public virtual Descriptable
{

    /**
    -----------------------------------------------------
    Serialization
    */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS;

    template<class Archive>
    void serialize(Archive &ar, const HLS version)
    {
        HL_SER_BASE;
        HL_SER(nDim_);
        HL_SER(nObjs_);
        HL_SER(powers_);
        HL_SER(shape_);

    }
    //@} Serialization -----------------------------------

public:


    typedef std::vector<HLS> ShapeType;

    /**
    Constructors & destructors
    */
    //@{

    HL_MultiIndexHelper();

    virtual ~HL_MultiIndexHelper();
    //@}


    /**
    Public class interface
    */
    //@{
    HL_CLASS_VAR_ACCESS_METHODS(HLS/*ClassVariableType*/, nDim/*classVariableName_no_underscore*/);
    HL_CLASS_VAR_ACCESS_METHODS(HLS/*ClassVariableType*/, nObjs/*classVariableName_no_underscore*/);
    HL_CLASS_VAR_ACCESS_METHODS_O(ShapeType/*ClassVariableType*/, shape/*classVariableName_no_underscore*/);


    void setShape(const ShapeType & shape);

    HLS get_nbPointsInDimension(HLS dimIdx) const
    {
        HL_SR(dimIdx<nDim_);
        return shape_[dimIdx];
    }

    HLS linearIdx(const HLMIDX & multiIndex) const;
    //@}


protected:

    /**
    Additional implementations
    */
    //@{
    /**
    Default initialization of the class vars.
    */
    void classDefaultInit();


    //@}


    /**
    Implementations of base class methods
    */
    //@{
    void descriptionImpl(std::ostream & os) const;
    //@}

protected:


    /**
    Class variables
    */
    //@{
    HLS nDim_;
    HLS nObjs_;
    std::vector<HLS> powers_;

    /**
    The collection is supposed to be organized as a vector<vector<vector<... >>>,
    where the nb of vectors is shape_.size()=nDim_ and the element access is done with a multi-index:

    element[m_0][m_1]...[m_{nDim-1}]

    with
    0<= m_0 < shape_[0]
    0<= m_1 < shape_[1]
    ...
    0<= m_{nDim-1} < shape_[nDim-1]


    The total nb of elements of the collection is:

    nObjs = shape_[0]*shape_[1]*...*shape_[nDim-1],
    */
    ShapeType shape_;

    //@}

}
; // end class HL_MultiIndexHelper


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MultiIndexHelper: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MultiArray
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131228
\brief Container for a multi-dimensional vector of objects of type T, where the nb of dimensions
is dynamically decided.
*/
template <class T>
class HL_MultiArray : public virtual HLSER::HL_Serializable, public virtual Descriptable
{

    /**
    -----------------------------------------------------
    Serialization
    */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS;

    template<class Archive>
    void serialize(Archive &ar, const HLS version)
    {

        HL_SER_BASE;
        HL_SER(objs_);
        HL_SER(multiIndexHelper_);
    }
    //@} Serialization -----------------------------------

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_MultiArray()
    {
        classDefaultInit();
    } // end HL_MultiArray

    virtual ~HL_MultiArray()
    {}
    //@}


    /**
    Public class interface
    */
    //@{






    HL_CLASS_VAR_ACCESS_METHODS_O(HL_MultiIndexHelper, multiIndexHelper);



    HLS get_nDim() const
    {

        return multiIndexHelper_.get_nDim();
    }


    HLS get_nbPointsInDimension(HLS dimIdx) const
    {
        return multiIndexHelper_.get_nbPointsInDimension(dimIdx);
    }



    void setShape(const HL_MultiIndexHelper::ShapeType & shape)
    {
        multiIndexHelper_.setShape(shape);
        objs_.resize(multiIndexHelper_.get_nObjs());

    } // end setShape

    const HL_MultiIndexHelper::ShapeType & get_shape() const
    {
        return multiIndexHelper_.get_shape();

    }

    virtual const T & operator[](const HLMIDX & multiIndex) const
    {
        return objs_[linearIdx(multiIndex)];
    }

    virtual T & operator[](const HLMIDX & multiIndex)
    {
        return objs_[linearIdx(multiIndex)];
    }
    //@}


protected:

    /**
    Additional implementations
    */
    //@{
    /**
    Default initialization of the class vars.
    */
    void classDefaultInit()
    {}

    HLS linearIdx(const HLMIDX & multiIndex) const
    {
        return multiIndexHelper_.linearIdx(multiIndex);
    }


    //@}


    /**
    Implementations of base class methods
    */
    //@{






    void descriptionImpl(std::ostream & os) const
    {
        Descriptable::descriptionImpl(os);
        hl_fillDescriptionStream(multiIndexHelper_);
    }
    //@}

protected:


    /**
    Class variables
    */
    //@{


    /**
    objs_ stores all the elements of the collection (notice that for large collections the memory
    could be fragmentaed if the T-type is non "plain").

    It holds that

    objs_.size()=multiIndexHelper_.nObjs().

    Check the code of multiIndexHelper_ to understand how a multi-index [m_0][m_1]...[m_{nDim-1}] is
    bi-univocally mapped to elements of objs_.
    */
    std::vector<T> objs_;

    /**
    Used to bi-univocally map elements of objs_ with a multi-index.
    */
    HL_MultiIndexHelper multiIndexHelper_;

    //@}

}
; // end class HL_MultiArray


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MultiArray: defines, utils, typedefs
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

typedef HLCTRS::HL_MultiArray<HLR> HL_RealMultiArray;

//------------------------------------------------------------------------------------------------------

#define HL_RealMultiArrayPtr BSP<HLCTRS::HL_RealMultiArray>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_SlicedMultiArray
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140104
\brief This class can be used to fix some of the coordinates of the input HL_MultiArray, in order to get
an array of lower dimensionality, i.e. a slice of the one represented by the HL_MultiArray.

Check also implementations for exact details.
*/
template <class T>
class HL_SlicedMultiArray : public virtual HL_MultiArray<T>
{

    /**
    -----------------------------------------------------
    Serialization
    */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS;

    template<class Archive>
    void serialize(Archive &ar, const HLS version)
    {

        HL_SERIALIZE_BASE_CLASS(HL_MultiArray<T>);
        HL_SER(inputMultiArray_);
        HL_SER(effMultiIndex_);
        HL_SER(freeDimIndexes_);


    }
    //@} Serialization -----------------------------------

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_SlicedMultiArray()
    {
        classDefaultInit();
    } // end HL_SlicedMultiArray

    virtual ~HL_SlicedMultiArray()
    {}
    //@}


    /**
    Public class interface
    */
    //@{



    /**
     * Let inputMultiArray_->get_shape()=inputShape
     * fixedCoords[i]=j(i) means that x_i is always forced to be equal to j(i),
     * where
     * i<inputShape.size()==inputMultiArray_->get_nDim()
     * and
     * j(i)<inputShape[i]=inputMultiArray_->get_nbPointsInDimension(i)
     * */
    void set_inputMultiArray(const BSP<HL_MultiArray<T> > &inputMultiArray,
                             const std::map<HLS, HLS> & fixedCoords)
    {
        inputMultiArray_=inputMultiArray;
        HL_PNN(inputMultiArray_);

        HLS input_nDim = inputMultiArray_->get_nDim();

        HLS nFixedCoords = fixedCoords.size();

        HL_SR(nFixedCoords<input_nDim);



        effMultiIndex_.resize(input_nDim, HL_NULL_INTEGER);

        std::map<HLS, HLS>::const_iterator fixedCoords_cIt = fixedCoords.begin();

        while(fixedCoords_cIt!=fixedCoords.end())
        {

            HLS i = fixedCoords_cIt->first;

            HL_SR(i<input_nDim);

            HLS j_i = fixedCoords_cIt->second;

            HL_SR(j_i<inputMultiArray_->get_nbPointsInDimension(i));

            effMultiIndex_[i] = j_i;

            ++fixedCoords_cIt;

        } // end for fixedCoord

        const HL_MultiIndexHelper::ShapeType & inputShape = inputMultiArray_->get_shape();

        HL_MultiIndexHelper::ShapeType effShape;

        freeDimIndexes_.clear();

        for(HLS i=0;i<input_nDim;++i)
        {
            if(fixedCoords.find(i)==fixedCoords.end())
            {
                freeDimIndexes_.push_back(i);
                effShape.push_back(inputShape[i]);
            }

        } // end for i

        HLS eff_nDim = input_nDim-nFixedCoords;

        HL_SR(effShape.size()==eff_nDim);


        /*
         * We do not call this method, since there's no need to create room for objs_
         *  but only to instantiate the right multiIndexHelper_ (i.e to call multiIndexHelper_.setShape(effShape))
         * */
        //HL_MultiArray<T>::setShape(effShape);
        HL_MultiArray<T>::multiIndexHelper_.setShape(effShape);




    } // end set_inputMultiArray


    const T & operator[](const HLMIDX & multiIndex) const
    {
        fillEffMultiIndex(multiIndex);
        return inputMultiArray_->operator[](effMultiIndex_);
    }

    T & operator[](const HLMIDX & multiIndex)
    {
        fillEffMultiIndex(multiIndex);
        return inputMultiArray_->operator[](effMultiIndex_);
    }


    //@}


protected:

    /**
    Additional implementations
    */
    //@{
    /**
    Default initialization of the class vars.
    */
    void classDefaultInit()
    {}

    //@}


    /**
    Implementations of base class methods
    */
    //@{








    void fillEffMultiIndex(const HLMIDX & multiIndex) const
    {

        HL_SR(multiIndex.size()==freeDimIndexes_.size());

        std::vector<HLS>::const_iterator freeDimIndexes_cIt = freeDimIndexes_.begin();

        BOOST_FOREACH(HLS idx, multiIndex)
        {

            HLS i = *freeDimIndexes_cIt;

            effMultiIndex_[i] = idx;

            ++freeDimIndexes_cIt;

        } // end for idx


    } // end fillEffMultiIndex





    void descriptionImpl(std::ostream & os) const
    {
        HL_MultiArray<T>::descriptionImpl(os);
    }
    //@}

protected:


    /**
    Class variables
    */
    //@{

    BSP<HL_MultiArray<T> > inputMultiArray_;


    //@}

    /**
     * Service class variables
    */
    //@{
    mutable HLMIDX effMultiIndex_;
    /**
     * freeDimIndexes_[i]=k(i) means that effMultiIndex_[k(i)] is not fixed: all other elements
     * of effMultiIndex_ have instead been fixed in method set_inputMultiArray
     * */
    std::vector<HLS> freeDimIndexes_;
    //@}


}
; // end class HL_SlicedMultiArray


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_SlicedMultiArray: defines, utils, typedefs
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


typedef HLCTRS::HL_SlicedMultiArray<HLR> HL_RealSlicedMultiArray;

//------------------------------------------------------------------------------------------------------

#define HL_RealSlicedMultiArrayPtr BSP<HLCTRS::HL_RealSlicedMultiArray>



} // end namespace HL_Containers
} //end namespace HorizonLib


#endif // _hl_multiArray_h_
