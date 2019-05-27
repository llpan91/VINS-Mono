# 1. feature tracker

pipline







## 1.2 question
1.2.1. what feature_tracker publish to which module ?

  publish =>
    sensor_msgs::PointCloudPtr feature_points(new sensor_msgs::PointCloud);
    sensor_msgs::ChannelFloat32 id_of_point;
    sensor_msgs::ChannelFloat32 u_of_point;
    sensor_msgs::ChannelFloat32 v_of_point;
    sensor_msgs::ChannelFloat32 velocity_x_of_point;
    sensor_msgs::ChannelFloat32 velocity_y_of_point;
  
  
  1) feature_points->header = img_msg->header;
     feature_points->header.frame_id = "world";
  
  2) geometry_msgs::Point32 p;
      p.x = un_pts[j].x;
      p.y = un_pts[j].y;
      p.z = 1;
      feature_points->points.push_back(p);
      
  3) feature_points->channels;
  
      feature_points->channels.push_back(id_of_point);
      feature_points->channels.push_back(u_of_point);
      feature_points->channels.push_back(v_of_point);
      feature_points->channels.push_back(velocity_x_of_point);
      feature_points->channels.push_back(velocity_y_of_point);
        
  id_of_point.values.push_back(p_id * NUM_OF_CAM + i);
  u_of_point.values.push_back(cur_pts[j].x);
  v_of_point.values.push_back(cur_pts[j].y);
  velocity_x_of_point.values.push_back(pts_velocity[j].x);
  velocity_y_of_point.values.push_back(pts_velocity[j].y);  
          
  // NOTE:
  idx of feature points are re-ordered