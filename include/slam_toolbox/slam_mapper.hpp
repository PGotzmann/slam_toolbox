/*
 * Author
 * Copyright (c) 2019 Samsung Research America
 *
 * THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE
 * COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE"). THE WORK IS PROTECTED BY
 * COPYRIGHT AND/OR OTHER APPLICABLE LAW. ANY USE OF THE WORK OTHER THAN AS
 * AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.
 *
 * BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO
 * BE BOUND BY THE TERMS OF THIS LICENSE. THE LICENSOR GRANTS YOU THE RIGHTS
 * CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND
 * CONDITIONS.
 *
 */

/* Author: Steven Macenski */

#ifndef SLAM_TOOLBOX_SLAM_MAPPER_H_
#define SLAM_TOOLBOX_SLAM_MAPPER_H_

#include "ros/ros.h"
#include "karto_sdk/Mapper.h"
#include "karto_sdk/Karto.h"
#include "tf2/utils.h"

namespace mapper_utils
{

using namespace ::karto;

class SMapper : public karto::Mapper
{
public:
  SMapper();
  ~SMapper();

  // get occupancy grid from scans
  karto::OccupancyGrid* getOccupancyGrid(const double& resolution);

  // convert Karto pose to TF pose
  tf2::Transform toTfPose(const karto::Pose2& pose) const;

  // convert TF pose to karto pose
  karto::Pose2 toKartoPose(const tf2::Transform& pose) const;

  void configure(const ros::NodeHandle& nh);
  virtual void Reset() override final;

  // processors
  kt_bool ProcessAtDock(LocalizedRangeScan* pScan);
  kt_bool ProcessAgainstNode(LocalizedRangeScan* pScan,  const int& nodeId);
  kt_bool ProcessAgainstNodesNearBy(LocalizedRangeScan* pScan);
  kt_bool ProcessLocalization(LocalizedRangeScan* pScan);

  karto::Dataset* getDataset();
  void setDataset(karto::Dataset*);

protected:
  LocalizationScanVertices m_LocalizationScanVertices;
  std::unique_ptr<karto::Dataset> dataset_;
};

} // end namespace

#endif //SLAM_TOOLBOX_SLAM_MAPPER_H_
