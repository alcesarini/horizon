from __future__ import unicode_literals

from django.db import models

from ..objects.objects import ObjectWithFreeRefName, Currency

from ..objects.objects import Dcc, PeriodUnit, instantiate_free_ref_name_field


from django.shortcuts import render
from django.http import HttpResponse
from django.shortcuts import get_object_or_404


# Create your models here.


#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------
# class Underlying
#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------

class Underlying(ObjectWithFreeRefName):
 
    currency = models.ForeignKey(Currency, 
	on_delete=models.SET_NULL,
	blank=True,
	null=True,)

 
 
    class Meta(ObjectWithFreeRefName.Meta):
        abstract=True
 
 
 
 
#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------
# class IborIndex
#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------

class IborIndex(Underlying):

    ref_name = instantiate_free_ref_name_field()

    dcc = models.ForeignKey(Dcc, 
	on_delete=models.SET_NULL,
	blank=True,
	null=True,)

    # The tenor of the ibor index
    periodUnit = models.ForeignKey(PeriodUnit, 
	on_delete=models.SET_NULL,
	blank=True,
	null=True,)


    # for ex.: 6 for euribor 6 months.
    periodNbUnits_integer = models.IntegerField(default=0)



 
    class Meta(Underlying.Meta):
        abstract=False



#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------
# class IborIndex
#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------

def iborIndex_detailView(request, ref_name):
    return HttpResponse("You're looking at iborIndex whose name is %s." % ref_name)
    
