from django.shortcuts import render
from django.http import HttpResponse
from django.shortcuts import get_object_or_404
from django.views.generic import ListView

from django.views.generic import CreateView
from django.views.generic import DetailView
from django.views.generic import UpdateView
from django.views.generic import DeleteView

from django.core.urlresolvers import reverse


# Create your views here.
from underlyings.underlyings import IborIndex
from .models import Post


import sys
#sys.path.append("../../../spyder/workspace")

print 50*"1"

import os

scriptPath = str(os.path.realpath(os.path.dirname(sys.argv[0])))

import re

print scriptPath

scriptPath = re.sub('website/hlwshorizon$', '', scriptPath)
scriptPath = scriptPath + 'spyder/workspace'

print scriptPath
#os.chdir(scriptPath)

sys.path.append(scriptPath)
print sys.path


#print os.path.dirname(__file__)

#sys.path.append(os.path.join(os.path.dirname(__file__), 
#'..', '..', 'spyder', 'workspace'))

print 50*"2"

#print sys.path


print 50*"3"
import horizonPy.test.hlpy_test


###################################
# PostListing
###################################


class PostListing(ListView):
    model = Post
    
###################################
# PostCreate
###################################


class PostCreate(CreateView):

    model = Post
    
    fields = ['title', 'content']
    
    
    def get_success_url(self):
       return reverse('hlwsfinapp:listing', kwargs={})


###################################
# PostDetail
###################################

class PostDetail(DetailView):

    model = Post    
    
###################################
# PostUpdate
###################################
    
class PostUpdate(UpdateView):
    model = Post    
    fields = ['title', 'content']
    
    def get_success_url(self):
        return reverse('hlwsfinapp:detail', kwargs={'pk': self.object.pk,})

###################################
# PostDelete
###################################

class PostDelete(DeleteView):
    model = Post

    def get_success_url(self):
        return reverse('hlwsfinapp:listing', kwargs={})


###################################
# index
###################################


#def index(request):
#    print "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
#    return HttpResponse("Hello, world. hlwsfinapp")
    
def index(request):
    iborIndex_list = IborIndex.objects.all()
    context = {'iborIndex_list': iborIndex_list}
    return render(request, 'hlwsfinapp/userIndexPage.html', context)
###################################
# calcolo
###################################
    
def calcolo(request):

    if request.method == 'POST':
        try:
    
            iborIndexName = request.POST.get('iborIndexNameField', None)
            
            print "iborIndexName=" + iborIndexName
            
            if iborIndexName == "":
                iborIndexName = request.POST.get('iborIndexNameField 1', None)

            print "iborIndexName=" + iborIndexName
            
            
            iborIndex = get_object_or_404(IborIndex, pk=iborIndexName)

            
            periodNbUnits_integer = iborIndex.periodNbUnits_integer


            risultato = horizonPy.test.hlpy_test.primoTest(periodNbUnits_integer)
    
            #do something with user

            stringRisultato = "risultato = " + str(risultato)
            
            
            return HttpResponse(stringRisultato) 
            
        except:
    
            return HttpResponse("calcolo PROBLEMA")
    else:
        print "calcolo ELSE"        

        return render(request, 'hlwsfinapp/calcolo.html')
        
 
 
 