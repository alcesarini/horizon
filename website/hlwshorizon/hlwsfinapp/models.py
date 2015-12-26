from __future__ import unicode_literals

from django.db import models

#from underlyings.underlyings import Underlying





# Create your models here.


class Post(models.Model):
    title = models.CharField( max_length=100, )
    content = models.TextField()
    
    def __str__(self):
        return self.title




#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------
# class HistorySeries
#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------

#class HistorySeries(models.Model):
#
#
#    description_text = models.CharField(max_length=hlws_description_text_max_length, default=hlws_description_text_default)
#
#
#
#    def __str__(self):
#	return self.description_text
# 


#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------
# class HistoryEntry
#--------------------------------------------------------------------------------
#--------------------------------------------------------------------------------

#class HistoryEntry(models.Model):
#
#   
#    pub_dateTimeRef = models.DateTimeField('date time reference', primary_key=True)
#     
#    lowPrice = models.FloatField(default=None)
#
#    highPrice = models.FloatField(default=None)
#
#    openPrice = models.FloatField(default=None)
#
#    closePrice = models.FloatField(default=None)
#
#
#    historySeries = models.ForeignKey(HistorySeries, 
#   	on_delete=models.CASCADE,
#	blank=False,
#	null=False,)
# 
#    description_text = models.CharField(max_length=hlws_description_text_max_length, default=hlws_description_text_default)
#
#    def __str__(self):
#	return str(self.historySeries) + " @ " + str(self.pub_dateTimeRef)



 










