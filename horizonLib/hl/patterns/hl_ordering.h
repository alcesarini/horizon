/**
FILE NAME= hl_ordering.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131130
*/
#ifndef _hl_ordering_h_
#define _hl_ordering_h_

#include <hl/patterns/hl_descriptable.h>


namespace HorizonLib
{

	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------
	// enum HL_Order
	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------

	enum HL_Order
	{
		HL_Order_InvalidMin=0,
		HL_Order_1_Less_2,
		HL_Order_1_Eq_2,
		HL_Order_1_Greater_2,
		HL_Order_InvalidMax

	}; // end enum HL_Order

	//------------------------------------------------------------------------------------------------------

	HL_ENUM_DESCRIPTION(
		HL_Order, 
		"HL_Order_InvalidMin",
		"HL_Order_1_Less_2",
		"HL_Order_1_Eq_2",
		"HL_Order_1_Greater_2",
		"HL_Order_InvalidMax"
		);


	//------------------------------------------------------------------------------------------------------

	template <class T1, class T2>
	HL_Order getOrder(const T1 & x1, const T2 & x2)
	{

		const std::type_info & t_x1 = typeid(x1);
		const std::type_info & t_x2 = typeid(x2);

		if(t_x1.before(t_x2))
			return HL_Order_1_Less_2;

		if(t_x2.before(t_x1))
			return HL_Order_1_Greater_2;

		HL_Order hl_Order= x1.getOrder(x2);	

		HL_SR(hl_Order>HL_Order_InvalidMin && hl_Order<HL_Order_InvalidMax);

		return hl_Order;
	} // end getOrder


	//------------------------------------------------------------------------------------------------------

	template <class T1, class T2>
	HL_Order getOrder(const BSP<T1> & x1, const BSP<T2> & x2)
	{

		HL_PNN(x1);
		HL_PNN(x2);

		return getOrder(*x1, *x2);	

	} // end getOrder

	//------------------------------------------------------------------------------------------------------

#define HL_DEFINE_ORDERING_STRICTLY_LESS(T) \
	inline bool operator<(const T & t1, const T & t2){return getOrder(t1, t2)==HL_Order_1_Less_2;}

	//------------------------------------------------------------------------------------------------------

#define HL_DEFINE_ORDERING_STRICTLY_GREATER(T) \
	inline bool operator>(const T & t1, const T & t2){return getOrder(t1, t2)==HL_Order_1_Greater_2;}

	//------------------------------------------------------------------------------------------------------

#define HL_DEFINE_ORDERING_EQ(T) \
	inline bool operator==(const T & t1, const T & t2){return getOrder(t1, t2)==HL_Order_1_Eq_2;}

	//------------------------------------------------------------------------------------------------------

#define HL_DEFINE_ORDERING_LESS_EQ(T) \
	inline bool operator<=(const T & t1, const T & t2){return !(t1>t2);}

	//------------------------------------------------------------------------------------------------------

#define HL_DEFINE_ORDERING_GREATER_EQ(T) \
	inline bool operator>=(const T & t1, const T & t2){return !(t1<t2);}


	//------------------------------------------------------------------------------------------------------

#define HL_DEFINE_ALL_ORDERING_SERVICE(T) \
	HL_DEFINE_ORDERING_STRICTLY_LESS(T) \
	HL_DEFINE_ORDERING_STRICTLY_GREATER(T) \
	HL_DEFINE_ORDERING_EQ(T) \
	HL_DEFINE_ORDERING_LESS_EQ(T) \
	HL_DEFINE_ORDERING_GREATER_EQ(T)

	//------------------------------------------------------------------------------------------------------

#define HL_DEFINE_ALL_ORDERING_OBJ(T) HL_DEFINE_ALL_ORDERING_SERVICE(T)

	//------------------------------------------------------------------------------------------------------

#define HL_DEFINE_ALL_ORDERING_SP(T) HL_DEFINE_ALL_ORDERING_SERVICE(BSP<T>)
	//------------------------------------------------------------------------------------------------------


	/** 
	Simply define this in order to define all the omparison operators between T-objects and between BSP<T>,
	where T-objects must define the virtual public method getOrder(..).
	Notice that the T-type must typically be some base class: the ordering will be then extened among T-derived
	types through the virtuality of method getOrder(..).
	*/
#define HL_DEFINE_ALL_ORDERING(T) \
	HL_DEFINE_ALL_ORDERING_OBJ(T) \
	HL_DEFINE_ALL_ORDERING_SP(T)


	//------------------------------------------------------------------------------------------------------

	template<class T>
	inline HL_Order plainOrder(const T & t1, const T & t2)
	{

		if(t1<t2)
			return HL_Order_1_Less_2;
		else if(t1>t2)
			return HL_Order_1_Greater_2;

		return HL_Order_1_Eq_2;

	} // end plainOrder

	//------------------------------------------------------------------------------------------------------

#define HL_PLAIN_ORDER_COMPARE(x, y) \
	{\
	HL_Order x_y_HL_Order = plainOrder(x, y);\
	if(x_y_HL_Order!=HL_Order_1_Eq_2){\
	return x_y_HL_Order;}\
	}

	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------
	// Check range ordering
	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------

	struct ComparisonOperator
	{

		HLSTRING orderingTypeString;
	}; // end struct ComparisonOperator
	//------------------------------------------------------------------------------------------------------

	struct ComparisonOperator_Less : public virtual ComparisonOperator
	{
		ComparisonOperator_Less(){orderingTypeString="<";}
		template <class T> bool operator()(const T & t_1, const T & t_2) const
		{
			return t_1<t_2;
		} // end operator()
	}; // end class ComparisonOperator_Less

	//------------------------------------------------------------------------------------------------------

	struct ComparisonOperator_LessEqual : public virtual ComparisonOperator	
	{
		ComparisonOperator_LessEqual(){orderingTypeString="<=";}
		template <class T> bool operator()(const T & t_1, const T & t_2) const
		{
			return t_1<=t_2;
		} // end operator()
	}; // end class ComparisonOperator_LessEqual

	//------------------------------------------------------------------------------------------------------

	struct ComparisonOperator_Greater : public virtual ComparisonOperator
	{
		ComparisonOperator_Greater(){orderingTypeString=">";}
		template <class T> bool operator()(const T & t_1, const T & t_2) const
		{
			return t_1>t_2;
		} // end operator()
	}; // end class ComparisonOperator_Greater

	//------------------------------------------------------------------------------------------------------

	struct ComparisonOperator_GreaterEqual : public virtual ComparisonOperator
	{
		ComparisonOperator_GreaterEqual(){orderingTypeString=">=";}
		template <class T> bool operator()(const T & t_1, const T & t_2) const
		{
			return t_1>=t_2;
		} // end operator()
	}; // end class ComparisonOperator_GreaterEqual


	//------------------------------------------------------------------------------------------------------

	template <class ForwardIterator, class ComparisonOperator>
	inline bool range_ordering_violation(ForwardIterator b, 
		ForwardIterator e, 
		HLSTRING & errString,
		const HLSTRING & rangeName,
		const ComparisonOperator & comparisonOperator)
	{
		errString="";

		if (b==e){
			// no violation
			return false;
		}

		ForwardIterator current = b;
		ForwardIterator next = b;

		while((++next)!=e) 
		{
			if(!comparisonOperator(*current, *next)){
				// violation
				HLI idx = current-b;
				std::stringstream ss;
				ss << ": ordering type " << comparisonOperator.orderingTypeString << " violated: " 
					<< rangeName << "[" << idx << "]=" <<  (*current) << ", " 
					<< rangeName << "[" << (idx+1) << "]=" <<  (*next);

				errString = ss.str();

				return true;
			}
			current=next;
		} // end while

		// no violation
		return false;

	} // end range_ordering_violation

	//------------------------------------------------------------------------------------------------------

#define	HL_REQ_RANGE_IS_ORDERED_SERVICE(b, e, rangeName, comparisonOperator) \
	{\
	HLSTRING __errString;\
	bool __ordering_violation = range_ordering_violation(b, \
	e, \
	__errString,\
	rangeName,\
	comparisonOperator);\
	HL_SRE(!__ordering_violation, __errString);\
	}

	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------

#define HL_REQ_RANGE_IS_ORDERED_L(b, e, rangeName) HL_REQ_RANGE_IS_ORDERED_SERVICE(b, e, #rangeName, ComparisonOperator_Less())

	//------------------------------------------------------------------------------------------------------

#define HL_REQ_RANGE_IS_ORDERED_LE(b, e, rangeName) HL_REQ_RANGE_IS_ORDERED_SERVICE(b, e, #rangeName, ComparisonOperator_LessEqual())

	//------------------------------------------------------------------------------------------------------

#define HL_REQ_RANGE_IS_ORDERED_G(b, e, rangeName) HL_REQ_RANGE_IS_ORDERED_SERVICE(b, e, #rangeName, ComparisonOperator_Greater())

	//------------------------------------------------------------------------------------------------------

#define HL_REQ_RANGE_IS_ORDERED_GE(b, e, rangeName) HL_REQ_RANGE_IS_ORDERED_SERVICE(b, e, #rangeName, ComparisonOperator_GreaterEqual())

	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------

#define HL_REQ_IS_ORDERED_L(container) HL_REQ_RANGE_IS_ORDERED_L(container.begin(), container.end(), container)

	//------------------------------------------------------------------------------------------------------

#define HL_REQ_IS_ORDERED_LE(container) HL_REQ_RANGE_IS_ORDERED_LE(container.begin(), container.end(), container)

	//------------------------------------------------------------------------------------------------------

#define HL_REQ_IS_ORDERED_G(container) HL_REQ_RANGE_IS_ORDERED_G(container.begin(), container.end(), container)

	//------------------------------------------------------------------------------------------------------

#define HL_REQ_IS_ORDERED_GE(container) HL_REQ_RANGE_IS_ORDERED_GE(container.begin(), container.end(), container)

	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------
	// HL_TEST_ordering
	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------


	/** 
	Test function for the behaviour of ordering defines.
	*/
	void HL_TEST_ordering();

	//------------------------------------------------------------------------------------------------------

	void HL_TEST_defines();

} //end namespace HorizonLib


#endif // _hl_ordering_h_