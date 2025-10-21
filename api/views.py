from django.shortcuts import render
from django.contrib.auth.models import User
from django.http import FileResponse
from rest_framework import generics, viewsets, permissions
from .serializers import UserSerializer, ImageSerializer
from .models import Image
from rest_framework.permissions import IsAuthenticated, AllowAny
from .helper import apply_filter   

class CreateUserView(generics.CreateAPIView): #needs to be a post method
    queryset = User.objects.all()
    serializer_class = UserSerializer
    permission_classes = [AllowAny]

class ImageViewSet(viewsets.ModelViewSet):  #POST = upload | GET id = get image | DELETE = delete 
    queryset = Image.objects.all()
    serializer_class = ImageSerializer
    permission_classes = [permissions.IsAuthenticated]

    def create(self, request, *args, **kwargs):
        serializer = self.get_serializer(data=request.data)
        serializer.is_valid(raise_exception=True)
        image_instance = serializer.save(user=request.user)

        filtered_path = apply_filter(image_instance.image.path, image_instance.filter)

        return FileResponse(
            open(filtered_path, "rb"),
            content_type="image/bmp"
        )