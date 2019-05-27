# 1. feature tracker

pipline

1) Initial FeatureTracker object;
    FeatureTracker trackerData[NUM_OF_CAM];

2) ReadImage 
    trackerData[i].readImage();
  a) if first_img =>   cv::goodFeaturesToTrack(forw_img,...); 
		       addPoints();
		       undistortedPoints();
  b) tracking => cv::calcOpticalFlowPyrLK(cur_img, forw_img, cur_pts, forw_pts,..);
		 rejectWithF();
		 setMask();
		 addPoints();
		 undistortedPoints();
		 
3) publish correspondences msg


# 2. feature_manager

    2.1 FeaturePerFrame  // struct of one feature in each frame
    2.2 FeaturePerId	 // struct of one feature correspondence to feature ID
    2.3 FeatureManager
    
    
  2.1 Struct of FeaturePerFrame

    FeaturePerFrame(const Eigen::Matrix<double, 7, 1> &_point, double td);
    
    include fellowing data structures:
	1) double cur_td;
	2) Vector3d point;
	3) Vector2d uv;
	4) Vector2d velocity;
	5) double z;
	6) bool is_used;
	7) double parallax;
	8) MatrixXd A;
	9) VectorXd b;
       10) double dep_gradient;
 
  2.2 Struct of FeaturePerId
    
    FeaturePerId(int _feature_id, int _start_frame);
    
    include fellowing data structures:
	1) const int feature_id;
	2) int start_frame;
	3) std::vector<FeaturePerFrame> feature_per_frame;
	4) int used_num;
	5) bool is_outlier;
	6) bool is_margin;
	7) double estimated_depth;
	8) int solve_flag;  // 0 haven't solve yet; 1 solve succ; 2 solve fail;
	9) Vector3d gt_p;
       10) int endFrame();
       
  2.3 Struct of FeatureManager
    
    std::list<FeaturePerId> feature;
 
    


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