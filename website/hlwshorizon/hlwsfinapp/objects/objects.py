from __future__ import unicode_literals

from django.db import models

# Create your models here.


#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------
# Defines
#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------




#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------
# class Object
#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------

class Object(models.Model):
    
    hlws_ref_name_max_length=100
 
    hlws_description_text_max_length = 500

    hlws_description_text_default = ""

    description_text = models.CharField(max_length=hlws_description_text_max_length,
                                        default=hlws_description_text_default,
                                        blank=True,
                                        null=True)
 
    ref_name=None
    
    def __str__(self):
        return str(self.ref_name)

    def description(self):
        return self.description_text
 
    class Meta:
        abstract=True
 

#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------
# class ObjectWithFreeRefName
#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------

'''
Cannot store an Obect in the db with ref_name="" (this is ensured by null=False)
furthermore blank=False says that an Obect with ref_name="" is not even logically valid.
So blank=False, null=False are logically coherent.
'''    

def instantiate_free_ref_name_field():
    
    return models.CharField(max_length=Object.hlws_ref_name_max_length, 
						primary_key=True,
						default=None, 
						blank=False, 
						null=False)

'''
The ref_name is free
'''    
class ObjectWithFreeRefName(Object):


 
    class Meta(Object.Meta):
        abstract=True

 
 
#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------
# class ObjectWithLimitedRefName
#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------

'''
The ref_name is limited among a set of names
'''    

class ObjectWithLimitedRefName(Object):



 
    class Meta(Object.Meta):
        abstract=True

 
 
#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------
# class Currency
#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------

class Currency(ObjectWithFreeRefName):

 
     ref_name = instantiate_free_ref_name_field()

     class Meta(ObjectWithFreeRefName.Meta):
         abstract=False




#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------
# class Dcc
#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------

class Dcc(ObjectWithLimitedRefName):

   
    ACT360 = 'act360'
    ACT365 = 'act365'

    DCC_CHOICES = (
	(None, 'Select a dcc'),
        (ACT360, 'Act360'),
        (ACT365, 'Act365'),
    )

    ref_name = models.CharField(max_length=Object.hlws_ref_name_max_length, 
		choices=DCC_CHOICES, 
		primary_key=True,
		default=None, 
		blank=False,
		null=False)
    
    class Meta(ObjectWithLimitedRefName.Meta):
        abstract=False
#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------
# class PeriodUnit
#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------

class PeriodUnit(ObjectWithLimitedRefName):

   
    DAYS = 'days'
    WEEKS = 'weeks'
    MONTHS = 'months'
    YEARS = 'years'

    PERIOD_UNIT_CHOICES = (
	(None, 'Select a period unit.'),
        (DAYS, 'Days'),
        (WEEKS, 'Weeks'),
        (MONTHS, 'Months'),
        (YEARS, 'Years'),
    )

    ref_name = models.CharField(max_length=Object.hlws_ref_name_max_length, 
		choices=PERIOD_UNIT_CHOICES, 
		primary_key=True,
		default=None, 
		blank=False,
		null=False)
  
    class Meta(ObjectWithLimitedRefName.Meta):
        abstract=False


 