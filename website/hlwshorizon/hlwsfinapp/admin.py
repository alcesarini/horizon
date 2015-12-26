from django.contrib import admin

# Register your models here.

from underlyings.underlyings import IborIndex

from objects.objects import Currency, Dcc, PeriodUnit

from .models import Post

#HistorySeries, HistoryEntry

admin.site.register(Post)

admin.site.register(Currency)

admin.site.register(Dcc)

admin.site.register(PeriodUnit)

#admin.site.register(HistorySeries)

#admin.site.register(HistoryEntry)

admin.site.register(IborIndex)

