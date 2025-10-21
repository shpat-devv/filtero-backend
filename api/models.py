from django.db import models
from django.contrib.auth.models import User

class UserProfile(models.Model):
    pfp_url = models.CharField(max_length=255, blank=True, null=True, default=None)
    email = models.CharField(max_length=255, blank=True, null=True, default=None)

    user = models.OneToOneField(User, on_delete=models.CASCADE, related_name="profile", blank=True, null=True, default=None)

    def __str__(self):
        return f"{self.user.username}'s profile"


class Image(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE, related_name="images")
    image = models.ImageField(upload_to="uploads/")
    uploaded_at = models.DateTimeField(auto_now_add=True)
    filter = models.CharField(max_length=10, blank=False, default="")