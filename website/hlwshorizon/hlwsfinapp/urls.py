from django.conf.urls import url

from . import views
from underlyings.underlyings import iborIndex_detailView

from .views import PostListing, PostCreate, PostDetail, PostUpdate, PostDelete

app_name = 'hlwsfinapp'
urlpatterns = [
    url(r'^$', views.index, name='index'),
    url(r'^calcolo/', views.calcolo, name='calcolo'), 
    url(r'^calcolo2/', views.calcolo2, name='calcolo2'), 
    url(r'^underlyings/iborIndexes/(?P<ref_name>[-\w]+)/$', iborIndex_detailView, name='iborIndex_detailView'),
    url(r'^posts/', PostListing.as_view(), name='listing'),
    url(r'^posts-create/$', PostCreate.as_view(), name='create'),
    url(r'^posts-detail/(?P<pk>\d+)/$', PostDetail.as_view(), name='detail'),
    url(r'^posts-detail/(?P<pk>\d+)/update/$', PostUpdate.as_view(), name='update'),
    url(r'^posts-detail/(?P<pk>\d+)/delete/$', PostDelete.as_view(), name='delete'),
]
