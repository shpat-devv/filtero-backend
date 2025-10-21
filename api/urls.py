from rest_framework.routers import DefaultRouter
from .views import ImageViewSet

router = DefaultRouter()
router.register("image", ImageViewSet)

urlpatterns = router.urls
